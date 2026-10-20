/* Shared light / dark mode switch for the labs.
   Include in <head> (so the page never flashes the wrong theme):
     <script src="../theme-toggle.js"></script>

   Sets  <html data-theme="light|dark">  and remembers the choice in
   localStorage, shared by every lab. Dark is the default.
   Adds a ☀ / ☾ button right after the lab's own "⌂ Home" link (copying its
   class so it matches), or at the start of the top bar if there is none.
   Pages restyle themselves with  :root[data-theme="light"]  rules; this file
   already covers the shared palette variables and the common lab layout.
   Shortcut: Ctrl/⌘+Shift+L. */
(function(){
  if(window.__apThemeInstalled) return;
  window.__apThemeInstalled = true;

  const KEY = 'ap-theme';
  const root = document.documentElement;
  let theme = 'dark';
  try{ if(localStorage.getItem(KEY) === 'light') theme = 'light'; }catch(_){}
  root.dataset.theme = theme;

  const style = document.createElement('style');
  style.id = 'ap-theme-style';
  style.textContent = `
:root[data-theme="light"]{
  color-scheme: light;
  --bg-0:#f5f6fb; --bg-1:#ffffff; --bg-2:#eceef6;
  --surface:rgba(20,20,60,0.035); --surface-2:rgba(20,20,60,0.065);
  --border:rgba(20,20,60,0.11); --border-strong:rgba(20,20,60,0.22);
  --text:#1b1b2f; --text-dim:#545670; --text-faint:#868aa3;
  --success:#12a073; --warn:#c77700; --error:#d63356;
  --shadow-lg: 0 24px 60px -30px rgba(60,50,140,0.28), 0 8px 24px -16px rgba(20,20,60,0.18);
  /* html/lab.html palette */
  --bg:#f5f6fb; --panel:#ffffff; --panel-2:#f0f2f8; --line:#dde2ee;
  --muted:#5b6785; --ink:#f5f6fb; --shadow: 0 10px 30px rgba(30,40,90,.10);
  --bad:#d63356;
}
:root[data-theme="light"] body{ background:var(--bg-0, var(--bg)); color:var(--text) }
/* the shared lab chrome: soft pastel backdrop instead of the starfield */
:root[data-theme="light"] #bg-3d{
  background:
    radial-gradient(1200px 700px at 8% -10%, rgba(124,92,255,0.12), transparent 60%),
    radial-gradient(1000px 600px at 110% 0%, rgba(53,208,255,0.10), transparent 60%),
    radial-gradient(900px 600px at 50% 130%, rgba(255,110,199,0.08), transparent 60%),
    #f5f6fb !important;
}
:root[data-theme="light"] body::after,
:root[data-theme="light"] body::before{ opacity:0 !important }
:root[data-theme="light"] .sidebar,
:root[data-theme="light"] aside.side{
  background:rgba(255,255,255,0.82) !important;
}
:root[data-theme="light"] ::-webkit-scrollbar-thumb{ background:rgba(20,20,60,0.16) }
:root[data-theme="light"] .sidebar-toggle{ background:rgba(20,20,60,0.03) }
:root[data-theme="light"] .sidebar-toggle:hover{ background:rgba(20,20,60,0.07) }

/* Dark islands: consoles, terminals and program output stay dark in light
   mode (their output colours are tuned for it), so give them back the dark
   palette locally. */
:root[data-theme="light"] :is(.console-card, .console-panel, .term, .out-terminal, .media-body, .preview-card:has(.out-titlebar, .console-titlebar, .phone-stage)){
  color-scheme: dark;
  --surface:rgba(255,255,255,0.04); --surface-2:rgba(255,255,255,0.07);
  --border:rgba(255,255,255,0.09); --border-strong:rgba(255,255,255,0.18);
  --text:#e8e8f3; --text-dim:#9a9ab0; --text-faint:#7a7a94;
  --success:#38d39f; --warn:#ffb547; --error:#ff5a7a;
  color:var(--text);
}
:root[data-theme="light"] :is(.console-card, .console-panel, .preview-card:has(.out-titlebar, .console-titlebar)){
  background:linear-gradient(180deg, #14142a, #0c0c1a) !important;
}

/* Glass cards of the editor labs (JS, TS, C++, CSS, Bootstrap, Mongo, Neo4j,
   React, React Native, C#) */
:root[data-theme="light"] :is(.top-bar, .editor-card, .preview-card:not(:has(.out-titlebar, .console-titlebar)), .viz-card, .media-panel){
  background:rgba(255,255,255,0.86) !important;
  box-shadow:0 18px 50px -30px rgba(40,40,110,0.30), 0 2px 8px -4px rgba(20,20,60,0.08);
}
:root[data-theme="light"] :is(.editor-card, .preview-card, .media-panel)::before{ opacity:.35 }
:root[data-theme="light"] .media-modal{ background:rgba(30,30,60,0.35) }
:root[data-theme="light"] :is(.action-btn:not(.run-btn, .stop-btn), .step-tab:not(.active), .editor-chrome .fs-ctl, .search){
  background:rgba(255,255,255,0.7);
}
/* pale tinted labels written for a dark background: darken them in place */
:root[data-theme="light"] :is(.editor-chrome .badge, #modeBadge, .dirty-mark, .file-link, .file-supergroup-head, .file-supergroup-head .count){
  filter:brightness(0.55) saturate(1.5);
}
:root[data-theme="light"] .action-btn .k{ background:rgba(20,20,60,0.07) }
:root[data-theme="light"] :is(.run-btn, .stop-btn) .k{ background:rgba(255,255,255,0.2) }
:root[data-theme="light"] .file-btn .lines{ background:rgba(20,20,60,0.05); color:var(--text-dim) }
:root[data-theme="light"] .file-btn.active{ color:var(--text) }
:root[data-theme="light"] .file-btn.active .lines{ color:var(--text) }
:root[data-theme="light"] .file-btn.active .label{ color:var(--text) }
:root[data-theme="light"] :is(.step-tab.active, .file-tab.active){ color:var(--text) }
:root[data-theme="light"] .file-link:hover{ color:var(--text) }
:root[data-theme="light"] .ambient{ opacity:.35 }

/* CodeMirror (dracula / material-darker in dark mode) → light editor */
:root[data-theme="light"] .CodeMirror{ background:#fbfbfe !important; color:#24292f !important }
:root[data-theme="light"] .CodeMirror .CodeMirror-gutters{ background:#f3f4f9 !important; border-right:1px solid var(--border) !important }
:root[data-theme="light"] .CodeMirror .CodeMirror-linenumber{ color:#9a9db3 !important }
:root[data-theme="light"] .CodeMirror .CodeMirror-cursor{ border-left-color:#1b1b2f !important }
:root[data-theme="light"] .CodeMirror .CodeMirror-activeline-background{ background:rgba(124,92,255,0.06) !important }
:root[data-theme="light"] .CodeMirror :is(.CodeMirror-selected, .CodeMirror-line::selection, .CodeMirror-line > span::selection, .CodeMirror-line > span > span::selection){ background:rgba(124,92,255,0.20) !important }
:root[data-theme="light"] .CodeMirror .CodeMirror-matchingbracket{ color:#0969da !important; text-shadow:none !important; background:rgba(9,105,218,0.10) }
:root[data-theme="light"] .CodeMirror :is(.cm-keyword, .cm-operator){ color:#cf222e !important }
:root[data-theme="light"] .CodeMirror :is(.cm-string, .cm-string-2){ color:#0a3069 !important }
:root[data-theme="light"] .CodeMirror :is(.cm-number, .cm-atom){ color:#0550ae !important }
:root[data-theme="light"] .CodeMirror :is(.cm-def){ color:#8250df !important }
:root[data-theme="light"] .CodeMirror :is(.cm-variable, .cm-punctuation, .cm-bracket){ color:#24292f !important }
:root[data-theme="light"] .CodeMirror :is(.cm-variable-2, .cm-property){ color:#0550ae !important }
:root[data-theme="light"] .CodeMirror :is(.cm-variable-3, .cm-type, .cm-builtin, .cm-qualifier){ color:#953800 !important }
:root[data-theme="light"] .CodeMirror :is(.cm-comment){ color:#6e7781 !important }
:root[data-theme="light"] .CodeMirror :is(.cm-meta){ color:#8250df !important }
:root[data-theme="light"] .CodeMirror :is(.cm-tag){ color:#116329 !important }
:root[data-theme="light"] .CodeMirror :is(.cm-attribute){ color:#0550ae !important }
:root[data-theme="light"] .CodeMirror :is(.cm-header, .cm-strong){ color:#0550ae !important }
:root[data-theme="light"] .CodeMirror .cm-link{ color:#0a3069 !important }
:root[data-theme="light"] .CodeMirror .cm-error{ color:#cf222e !important; background:rgba(207,34,46,0.08) !important }
:root[data-theme="light"]{
  /* C++ labs colour their own tokens / snippets with these */
  --kw-color:#0550ae; --type-color:#8250df; --string-color:#116329;
  --comment-color:#6e7781; --num-color:#953800;
}

/* Git / Jira / Docker lesson layout */
:root[data-theme="light"] .panel{ background:rgba(255,255,255,0.86) }
:root[data-theme="light"] .explain{ color:#33354a }
:root[data-theme="light"] :is(.explain h4, .terms dt){ color:var(--text) }
:root[data-theme="light"] :is(.explain, .step p, .narr) code{ background:rgba(20,20,60,0.06) }
:root[data-theme="light"] :is(.explain, .step, .narr) code{ filter:brightness(0.5) saturate(1.6) }
:root[data-theme="light"] .lesson-btn.active{ color:var(--text) }
:root[data-theme="light"] :is(.tab.active, .side-ctl button.active, .split-ctl button.active){ color:var(--text); background:#fff }
:root[data-theme="light"] :is(.collapse-btn, .side-ctl button, .split-ctl button, .fsv-head button, .pager button):hover{ color:var(--text) }

.ap-theme-btn{
  display:inline-flex; align-items:center; justify-content:center; gap:7px;
  cursor:pointer; font-family:inherit; white-space:nowrap;
}
.ap-theme-btn.back-link{ width:100%; justify-content:flex-start; margin-top:8px !important; background:none }
.ap-theme-btn.ap-theme-float{
  position:fixed; bottom:16px; right:16px; z-index:99998;
  padding:9px 14px; border-radius:999px; font:600 12.5px/1 'Inter',system-ui,sans-serif;
  color:var(--text,#e8e8f3); background:var(--bg-1,var(--panel,#111));
  border:1px solid var(--border-strong,var(--line,rgba(255,255,255,0.18)));
  box-shadow:0 10px 28px -12px rgba(0,0,0,0.45);
}
@media print{ .ap-theme-btn{ display:none } }`;
  (document.head || root).appendChild(style);

  let btn = null, iconOnly = false;
  function label(){
    if(!btn) return;
    const light = root.dataset.theme === 'light';
    const ico = light ? '☾' : '☀', txt = light ? 'Dark' : 'Light';
    // Match a "<span class=ico>⌂</span><span class=t>Home</span>" home link,
    // so a collapsed sidebar shows just the icon here too.
    btn.innerHTML = iconOnly ? '<span class="ico">' + ico + '</span><span class="t">' + txt + '</span>' : ico + ' ' + txt;
    btn.title = 'Switch to ' + (light ? 'dark' : 'light') + ' mode (Ctrl+Shift+L)';
    btn.setAttribute('aria-pressed', String(light));
  }
  function set(t){
    theme = t;
    root.dataset.theme = t;
    try{ localStorage.setItem(KEY, t); }catch(_){}
    label();
    // Canvases / editors that read colours at draw time can listen for this.
    window.dispatchEvent(new CustomEvent('ap-themechange', { detail: t }));
    document.querySelectorAll('.CodeMirror').forEach(el => el.CodeMirror && el.CodeMirror.refresh());
  }
  const toggle = () => set(root.dataset.theme === 'light' ? 'dark' : 'light');

  function install(){
    if(document.querySelector('.ap-theme-btn')) return;
    btn = document.createElement('button');
    btn.type = 'button';
    const home = document.querySelector('a[href="../index.html"]');
    const bar = document.querySelector('.top-bar, header.top');
    if(home){
      btn.className = home.className + ' ap-theme-btn';
      iconOnly = !!home.querySelector('.ico');
      if(home.getAttribute('style')) btn.setAttribute('style', home.getAttribute('style'));
      home.after(btn);
    }else if(bar){
      btn.className = 'sidebar-toggle ap-theme-btn';
      btn.style.width = 'auto'; btn.style.padding = '0 12px';
      bar.appendChild(btn);
    }else{
      btn.className = 'ap-theme-btn ap-theme-float';
      document.body.appendChild(btn);
    }
    btn.addEventListener('click', toggle);
    label();
  }

  document.addEventListener('keydown', e => {
    if((e.ctrlKey || e.metaKey) && e.shiftKey && (e.key === 'L' || e.key === 'l')){
      e.preventDefault(); toggle();
    }
  });
  // Another lab tab changed the theme — follow it.
  window.addEventListener('storage', e => {
    if(e.key === KEY && (e.newValue === 'light' || e.newValue === 'dark') && e.newValue !== root.dataset.theme) set(e.newValue);
  });

  if(document.body) install();
  else document.addEventListener('DOMContentLoaded', install);
})();
