/* ─────────────────────────────────────────────────────────────
   shared lab runtime
   ───────────────────────────────────────────────────────────── */

import * as THREE from 'https://unpkg.com/three@0.160.0/build/three.module.js';

export const PALETTE = {
  void:    0x05060d,
  ink:     0xe6ecff,
  inkDim:  0x8b93b8,
  cyan:    0x35d0ff,
  amber:   0xffb454,
  magenta: 0xff5cab,
  violet:  0x7c5cff,
  lime:    0xb9ff5c,
  err:     0xff5c70,
  ok:      0x5cffb4,
};

/* ─── small DOM helpers ─── */
export const $  = (s, r=document) => r.querySelector(s);
export const $$ = (s, r=document) => [...r.querySelectorAll(s)];
export const el = (tag, attrs={}, ...kids) => {
  const n = document.createElement(tag);
  for (const k in attrs){
    if (k === 'class') n.className = attrs[k];
    else if (k === 'html') n.innerHTML = attrs[k];
    else if (k.startsWith('on')) n.addEventListener(k.slice(2), attrs[k]);
    else n.setAttribute(k, attrs[k]);
  }
  for (const c of kids){
    if (c == null) continue;
    n.appendChild(c.nodeType ? c : document.createTextNode(c));
  }
  return n;
};

/* ─── three.js scene wrapper ─── */
export function createScene({mount, camera = {pos:[0,4,18], lookAt:[0,0,0]}}){
  const w = mount.clientWidth, h = mount.clientHeight;
  const scene = new THREE.Scene();
  scene.fog = new THREE.Fog(0x04050b, 26, 90);

  const cam = new THREE.PerspectiveCamera(45, w/h, 0.1, 200);
  cam.position.set(...camera.pos);
  cam.lookAt(new THREE.Vector3(...camera.lookAt));

  const renderer = new THREE.WebGLRenderer({antialias:true, alpha:true});
  renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
  renderer.setSize(w, h, false);
  renderer.setClearColor(0x000000, 0);
  renderer.outputColorSpace = THREE.SRGBColorSpace;
  mount.appendChild(renderer.domElement);

  // lighting
  const amb = new THREE.AmbientLight(0xb8c4ff, 0.55);
  scene.add(amb);
  const key = new THREE.DirectionalLight(0xffffff, 1.05);
  key.position.set(5, 10, 8);
  scene.add(key);
  const rim = new THREE.DirectionalLight(0x35d0ff, 0.45);
  rim.position.set(-8, 4, -6);
  scene.add(rim);
  const mag = new THREE.PointLight(0xff5cab, 0.65, 40);
  mag.position.set(-6, 2, 6);
  scene.add(mag);

  // starfield (very subtle)
  {
    const g = new THREE.BufferGeometry();
    const N = 320, arr = new Float32Array(N*3);
    for (let i=0;i<N;i++){
      arr[i*3]   = (Math.random()-0.5)*120;
      arr[i*3+1] = (Math.random()-0.5)*80 + 8;
      arr[i*3+2] = (Math.random()-0.5)*120 - 20;
    }
    g.setAttribute('position', new THREE.BufferAttribute(arr, 3));
    const m = new THREE.PointsMaterial({color:0x9aa6d6, size:0.05, transparent:true, opacity:0.45});
    scene.add(new THREE.Points(g, m));
  }

  // floor: large faint disc + radial grid
  {
    const disc = new THREE.Mesh(
      new THREE.CircleGeometry(60, 64),
      new THREE.MeshBasicMaterial({color:0x0a0e1c, transparent:true, opacity:0.65, side:THREE.DoubleSide})
    );
    disc.rotation.x = -Math.PI/2;
    disc.position.y = -3.5;
    scene.add(disc);
    const grid = new THREE.GridHelper(80, 40, 0x35d0ff, 0x1a2240);
    grid.material.opacity = 0.18; grid.material.transparent = true;
    grid.position.y = -3.49;
    scene.add(grid);
  }

  // camera drift
  const drift = {t:0, base: cam.position.clone(), enabled:true};
  function tick(){
    drift.t += 0.0035;
    if (drift.enabled){
      cam.position.x = drift.base.x + Math.sin(drift.t*0.7)*0.55;
      cam.position.y = drift.base.y + Math.cos(drift.t*0.5)*0.25;
      cam.lookAt(0, camera.lookAt[1], camera.lookAt[2]);
    }
    renderer.render(scene, cam);
    requestAnimationFrame(tick);
  }
  requestAnimationFrame(tick);

  // resize
  const onResize = () => {
    const W = mount.clientWidth, H = mount.clientHeight;
    cam.aspect = W/H; cam.updateProjectionMatrix();
    renderer.setSize(W, H, false);
  };
  window.addEventListener('resize', onResize);

  return {scene, cam, renderer, drift};
}

/* ─── small tween util ─── */
export function tween(obj, prop, to, ms=420, ease=easeOutCubic){
  return new Promise(res => {
    const from = obj[prop];
    const t0 = performance.now();
    function step(now){
      const k = Math.min(1, (now-t0)/ms);
      obj[prop] = from + (to - from)*ease(k);
      if (k<1) requestAnimationFrame(step); else res();
    }
    requestAnimationFrame(step);
  });
}
export function tweenVec(vec, to, ms=420, ease=easeOutCubic){
  return new Promise(res => {
    const from = vec.clone();
    const t0 = performance.now();
    function step(now){
      const k = Math.min(1, (now-t0)/ms);
      vec.lerpVectors(from, to, ease(k));
      if (k<1) requestAnimationFrame(step); else res();
    }
    requestAnimationFrame(step);
  });
}
export const easeOutCubic = t => 1 - Math.pow(1-t, 3);
export const easeInOutCubic = t => t<0.5 ? 4*t*t*t : 1 - Math.pow(-2*t+2,3)/2;
export const sleep = ms => new Promise(r => setTimeout(r, ms));

/* ─── undo stack ─── */
export function createHistory(){
  const stack = [];
  return {
    push(snapshot){ stack.push(snapshot); },
    pop(){ return stack.pop(); },
    size(){ return stack.length; },
    clear(){ stack.length = 0; },
  };
}

/* ─── on-screen log ─── */
export function createLog(mountSel='#log'){
  const root = typeof mountSel === 'string' ? $(mountSel) : mountSel;
  const list = el('div', {class:'log-list'});
  root.appendChild(el('h3', {}, 'Trace'));
  root.appendChild(list);
  function fmtTime(){
    const d = new Date();
    return String(d.getHours()).padStart(2,'0')+':'+String(d.getMinutes()).padStart(2,'0')+':'+String(d.getSeconds()).padStart(2,'0');
  }
  return {
    say(html){
      const row = el('div', {class:'entry'},
        el('span', {class:'t'}, fmtTime()),
        el('span', {class:'e', html})
      );
      list.prepend(row);
      while (list.childElementCount > 80) list.lastElementChild.remove();
    },
    clear(){ list.innerHTML = ''; },
  };
}

/* ─── complexity readout ─── */
export function createComplexityPanel(mount, rows){
  const wrap = el('div', {class:'cx-panel'});
  for (const r of rows){
    wrap.appendChild(el('div', {class:'cx-row'},
      el('span', {class:'key'}, r.key),
      el('span', {class:'val'}, r.val)
    ));
  }
  const now = el('div', {class:'cx-now'},
    el('span', {html:'<span class="badge"></span><span class="now-text">idle</span>'}),
    el('span', {class:'now-cx', html:'&nbsp;'})
  );
  wrap.appendChild(now);
  mount.appendChild(wrap);
  return {
    set(opLabel, cx){
      now.querySelector('.now-text').textContent = opLabel;
      now.querySelector('.now-cx').innerHTML = cx;
    },
  };
}

/* ─── wire back button + clock ─── */
export function mountTopbar({title, sub, back='index.html'}){
  const root = $('#topbar');
  if (!root) return;
  root.innerHTML = '';
  root.appendChild(el('a', {class:'btn-back', href:back, 'aria-label':'Back to labs'},
    el('span', {class:'arrow', html:'&#8592;'}), 'labs'));
  root.appendChild(el('div', {class:'brand'},
    el('div', {class:'brand-mark'}),
    el('div', {},
      el('div', {class:'brand-title'}, title),
      el('div', {class:'brand-sub'}, sub),
    )
  ));
  root.appendChild(el('div', {class:'spacer'}));
  const clock = el('div', {class:'stage-tag'}, '');
  root.appendChild(clock);
  const tick = () => {
    const d = new Date();
    clock.innerHTML = `<b>T</b>&nbsp; ${String(d.getHours()).padStart(2,'0')}:${String(d.getMinutes()).padStart(2,'0')}:${String(d.getSeconds()).padStart(2,'0')}`;
  };
  tick(); setInterval(tick, 1000);
}

/* ─── input parsing util ─── */
export function parseNum(str, fallback=null){
  if (str == null || str === '') return fallback;
  const n = Number(str);
  if (Number.isFinite(n)) return n;
  return fallback;
}
export function parseList(str){
  if (!str) return [];
  return String(str).split(/[,\s]+/).filter(Boolean).map(Number).filter(Number.isFinite);
}
export function randomInt(a, b){ return a + Math.floor(Math.random()*(b-a+1)); }
