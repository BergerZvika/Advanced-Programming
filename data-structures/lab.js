/* ─────────────────────────────────────────────────────────────
   shared lab runtime
   ───────────────────────────────────────────────────────────── */

import * as THREE from 'https://unpkg.com/three@0.160.0/build/three.module.js';
import { OrbitControls } from 'https://unpkg.com/three@0.160.0/examples/jsm/controls/OrbitControls.js';

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

  // orbit / pan / zoom controls
  const controls = new OrbitControls(cam, renderer.domElement);
  controls.enableDamping  = true;
  controls.dampingFactor  = 0.08;
  controls.target.set(...camera.lookAt);
  controls.minDistance    = 4;
  controls.maxDistance    = 90;
  controls.maxPolarAngle  = Math.PI * 0.92;  // don't let user look from underneath the grid
  controls.zoomSpeed      = 0.9;
  controls.rotateSpeed    = 0.75;
  controls.panSpeed       = 0.75;
  controls.screenSpacePanning = true;
  controls.update();

  // render loop
  function tick(){
    controls.update();
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

  return {scene, cam, renderer, controls};
}

/* ─── stepper · pause/play/single-step ─── */
export const stepper = {
  paused: false,
  resume: null,    // resolver for in-flight pause
  speed: 1,        // 1 = normal, >1 = faster
  stepOnce: false, // run forward without pausing until next checkpoint (animations still play)
  checkpoints: [], // {label, undo: async () => void}
  onState: null,   // callback(state) for UI updates
};
export function stepperKick(){
  if (stepper.resume){ const r = stepper.resume; stepper.resume = null; r(); }
}
export function stepperPlay(){ stepper.paused = false; stepperKick(); stepper.onState && stepper.onState('playing'); }
export function stepperPause(){ stepper.paused = true; stepper.onState && stepper.onState('paused'); }
export function stepperToggle(){ stepper.paused ? stepperPlay() : stepperPause(); }
// "fast forward" button now means "single step with animation": advance to the
// next checkpoint at normal speed instead of jumping over the animations.
export function stepperFastForward(){ stepper.stepOnce = true; stepperKick(); }
export async function stepperCheckpoint(label, undoFn){
  if (undoFn) stepper.checkpoints.push({label: label || '', undo:undoFn});
  if (label != null && stepper.onState) stepper.onState(label);
  // Arrival at the next checkpoint ends the single-step pass so the next
  // sleep/tween honors `paused` again.
  stepper.stepOnce = false;
  if (stepper.paused){
    await new Promise(r => stepper.resume = r);
  }
}
export async function stepperUndo(){
  const cp = stepper.checkpoints.pop();
  if (!cp) return false;
  if (stepper.onState) stepper.onState('undo · '+cp.label);
  await cp.undo();
  return true;
}
export function stepperClear(){ stepper.checkpoints.length = 0; }

/* ─── small tween util · pause-aware ─── */
// sleep / tween / tweenVec all honor stepper.paused — but if stepper.stepOnce
// is set they treat the scene as if it's playing (animation runs at normal
// speed). That way a single-step click shows the animation between two
// checkpoints instead of jumping past it instantly.
export function tween(obj, prop, to, ms=420, ease=easeOutCubic){
  return new Promise(res => {
    const from = obj[prop];
    let t0 = performance.now(), pausedAt = 0, totalPause = 0;
    function step(now){
      if (stepper.paused && !stepper.stepOnce){
        if (!pausedAt) pausedAt = now;
        requestAnimationFrame(step); return;
      }
      if (pausedAt){ totalPause += now - pausedAt; pausedAt = 0; }
      const elapsed = (now - t0 - totalPause) * stepper.speed;
      const k = Math.min(1, elapsed/ms);
      obj[prop] = from + (to - from)*ease(k);
      if (k<1) requestAnimationFrame(step); else res();
    }
    requestAnimationFrame(step);
  });
}
export function tweenVec(vec, to, ms=420, ease=easeOutCubic){
  return new Promise(res => {
    const from = vec.clone();
    let t0 = performance.now(), pausedAt = 0, totalPause = 0;
    function step(now){
      if (stepper.paused && !stepper.stepOnce){
        if (!pausedAt) pausedAt = now;
        requestAnimationFrame(step); return;
      }
      if (pausedAt){ totalPause += now - pausedAt; pausedAt = 0; }
      const elapsed = (now - t0 - totalPause) * stepper.speed;
      const k = Math.min(1, elapsed/ms);
      vec.lerpVectors(from, to, ease(k));
      if (k<1) requestAnimationFrame(step); else res();
    }
    requestAnimationFrame(step);
  });
}
export const easeOutCubic = t => 1 - Math.pow(1-t, 3);
export const easeInOutCubic = t => t<0.5 ? 4*t*t*t : 1 - Math.pow(-2*t+2,3)/2;
export async function sleep(ms){
  let remaining = ms;
  while (remaining > 0){
    if (stepper.paused && !stepper.stepOnce){
      await new Promise(r => stepper.resume = r);
    }
    const chunk = Math.min(remaining, 32);
    await new Promise(r => setTimeout(r, chunk / Math.max(0.1, stepper.speed)));
    remaining -= chunk;
  }
}

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
    set(opLabel, cxLabel){
      now.querySelector('.now-text').textContent = opLabel;
      now.querySelector('.now-cx').innerHTML = cxLabel;
      // mirror into the player transport status bar so the user sees what's
      // happening without having to look at two places at once
      if (stepper.onState) stepper.onState(opLabel);
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

/* ─── 3D arrow indicator (shaft + cone + halo + optional text label) ─── */
// default arrow points in -Y (down). Rotate the returned group to re-aim:
//   up:    rotation.x = Math.PI  (or rotation.z = Math.PI)
//   left:  rotation.z =  Math.PI/2
//   right: rotation.z = -Math.PI/2
export function makeArrow3D({color = 0x5cffb4, label = '', length = 1.5, labelSide = 'top'} = {}){
  const grp = new THREE.Group();

  const mat = new THREE.MeshPhysicalMaterial({
    color, emissive:color, emissiveIntensity:0.45,
    metalness:0.5, roughness:0.25, clearcoat:0.5
  });

  const shaft = new THREE.Mesh(new THREE.CylinderGeometry(0.085, 0.085, length, 18), mat);
  shaft.position.y = -length/2;
  grp.add(shaft);

  const tip = new THREE.Mesh(new THREE.ConeGeometry(0.24, 0.5, 22), mat);
  tip.rotation.x = Math.PI;            // apex toward -Y
  tip.position.y = -length - 0.25;
  grp.add(tip);

  if (label){
    const c = document.createElement('canvas'); c.width = 512; c.height = 160;
    const ctx = c.getContext('2d');
    ctx.fillStyle = '#' + color.toString(16).padStart(6, '0');
    ctx.font = '800 78px IBM Plex Mono, monospace';
    ctx.textAlign = 'center'; ctx.textBaseline = 'middle';
    ctx.shadowColor = 'rgba(0,0,0,0.85)'; ctx.shadowBlur = 14;
    ctx.fillText(label, 256, 80);
    const tex = new THREE.CanvasTexture(c); tex.minFilter = THREE.LinearFilter;
    const spr = new THREE.Sprite(new THREE.SpriteMaterial({map:tex, transparent:true, depthTest:false}));
    spr.renderOrder = 12;
    spr.scale.set(1.9, 0.6, 1);
    if (labelSide === 'top')    spr.position.set(0,  0.45, 0);
    if (labelSide === 'bottom') spr.position.set(0, -length - 0.75, 0);
    grp.add(spr);
  }

  return {group: grp, shaft, tip,
          setColor(c){ mat.color.setHex(c); mat.emissive.setHex(c); }};
}

/* ─── player UI · play/pause/back/forward ─── */
export function mountPlayer({mount, onBack}){
  const root = typeof mount === 'string' ? $(mount) : mount;
  if (!root) return null;
  const playBtn  = el('button', {class:'pl-btn pl-play',  title:'play / pause (Space)', html:'<svg viewBox="0 0 24 24" width="14" height="14" fill="currentColor"><path d="M8 5v14l11-7z"/></svg>'});
  const pauseBtn = el('button', {class:'pl-btn pl-pause hidden', title:'pause (Space)', html:'<svg viewBox="0 0 24 24" width="14" height="14" fill="currentColor"><path d="M6 5h4v14H6zM14 5h4v14h-4z"/></svg>'});
  const backBtn  = el('button', {class:'pl-btn',  title:'step backward (←)', html:'<svg viewBox="0 0 24 24" width="14" height="14" fill="currentColor"><path d="M6 6h2v12H6zM20 6 9 12l11 6z"/></svg>'});
  const fwdBtn   = el('button', {class:'pl-btn',  title:'skip to end of step (→)', html:'<svg viewBox="0 0 24 24" width="14" height="14" fill="currentColor"><path d="M16 6h2v12h-2zM4 6l11 6L4 18z"/></svg>'});
  // continuous speed slider: 0.1× ··· 5× with smooth steps
  const speedSlider = el('input', {type:'range', class:'pl-speed-slider', min:'0.1', max:'5', step:'0.05', value:'1', title:'speed'});
  const speedVal    = el('span', {class:'pl-speed-val'}, '1.00×');
  const speedWrap   = el('div', {class:'pl-speed-wrap', title:'animation speed'}, speedSlider, speedVal);
  const bar = el('div', {class:'pl-bar'}, backBtn, playBtn, pauseBtn, fwdBtn, speedWrap);
  root.appendChild(bar);

  function setMode(playing){
    if (playing){ playBtn.classList.add('hidden'); pauseBtn.classList.remove('hidden'); }
    else        { playBtn.classList.remove('hidden'); pauseBtn.classList.add('hidden'); }
  }
  setMode(false);  // start as "play" icon visible (i.e., paused/idle look)

  // wire
  playBtn .addEventListener('click', () => { stepperPlay();  setMode(true); });
  pauseBtn.addEventListener('click', () => { stepperPause(); setMode(false); });
  fwdBtn  .addEventListener('click', () => { stepperFastForward(); });
  backBtn .addEventListener('click', async () => {
    const ok = await stepperUndo();
    if (!ok && onBack) onBack();   // fall back to lab's op-undo if checkpoints empty
  });
  // continuous speed: 0.10× ··· 5.00×
  function applySpeed(){
    const v = parseFloat(speedSlider.value) || 1;
    stepper.speed = v;
    speedVal.textContent = (v < 10 ? v.toFixed(2) : v.toFixed(1)) + '×';
  }
  speedSlider.addEventListener('input', applySpeed);
  speedSlider.addEventListener('change', applySpeed);
  applySpeed();

  // No status text in the bar — cx.set still updates the side-panel readout
  // via createComplexityPanel; the bar stays a fixed-size button row.
  stepper.onState = null;

  // keyboard
  window.addEventListener('keydown', e => {
    if (e.target.tagName === 'INPUT') return;
    if (e.code === 'Space'){ e.preventDefault(); stepperToggle(); setMode(!stepper.paused); }
    else if (e.code === 'ArrowRight'){ stepperFastForward(); }
    else if (e.code === 'ArrowLeft'){ backBtn.click(); }
  });

  return {setMode, status};
}

/* ─── preset toolbar (default-state buttons under the stage) ─── */
// presets: array of {name, desc, apply: async ()=>void}
export function mountPresets({mount, label = 'presets', presets = []}){
  const root = typeof mount === 'string' ? $(mount) : mount;
  if (!root) return;
  root.innerHTML = '';
  root.appendChild(el('div', {class:'presets-label'}, label));
  for (const p of presets){
    const btn = el('button', {class:'preset-btn', type:'button', title: p.desc || ''},
      el('span', {class:'preset-name'}, p.name),
      el('span', {class:'preset-desc'}, p.desc || '')
    );
    btn.addEventListener('click', async () => {
      try { await p.apply(); }
      catch (e) { console.error('preset failed', e); }
    });
    root.appendChild(btn);
  }
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
