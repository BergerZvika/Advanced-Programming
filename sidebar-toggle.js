/* Shared "hide sidebar" toggle for the labs.
   Include with:  <script src="../sidebar-toggle.js"></script>   (just before </body>)

   Defaults fit the standard lab layout:  .app > aside.sidebar  +  header.top-bar
   Override per page with data attributes on the <script> tag:
     data-app=".shell"  data-sidebar="aside.side"  data-bar="header.top"
   Adds a ⟨ / ☰ button at the start of the bar, Ctrl/⌘+B shortcut,
   and remembers the choice per lab in localStorage. */
(function(){
  const me = document.currentScript;
  const opt = k => (me && me.dataset[k]) || null;
  const app  = document.querySelector(opt('app') || '.app');
  const side = document.querySelector(opt('sidebar') || '.sidebar');
  const bar  = document.querySelector(opt('bar') || '.top-bar');
  if(!app || !side || !bar) return;

  const style = document.createElement('style');
  style.textContent = `
.sb-app{ transition: grid-template-columns .25s ease }
.sb-app.sb-collapsed{ grid-template-columns: 0 minmax(0,1fr) !important }
.sb-app.sb-collapsed > .sb-side{ padding:0 !important; border:none !important; overflow:hidden !important; visibility:hidden }
@media (max-width: 980px){
  .sb-app.sb-collapsed{ grid-template-columns: minmax(0,1fr) !important }
  .sb-app.sb-collapsed > .sb-side{ display:none !important }
}
.sidebar-toggle{
  width:36px; height:36px; flex-shrink:0; border-radius:10px; cursor:pointer;
  border:1px solid var(--border, var(--line, rgba(255,255,255,0.09)));
  background:rgba(255,255,255,0.03);
  color:var(--text-dim, var(--muted, #9a9ab0)); font-size:16px; line-height:1;
  display:inline-flex; align-items:center; justify-content:center;
  transition: background .15s, color .15s, border-color .15s;
}
.sidebar-toggle:hover{
  background:rgba(255,255,255,0.07); color:var(--text, #e8e8f3);
  border-color:var(--border-strong, rgba(255,255,255,0.18));
}`;
  document.head.appendChild(style);

  app.classList.add('sb-app');
  side.classList.add('sb-side');

  const btn = document.createElement('button');
  btn.type = 'button';
  btn.className = 'sidebar-toggle';
  bar.insertBefore(btn, bar.firstChild);

  const KEY = 'sidebarCollapsed:' + location.pathname;
  function set(collapsed, save){
    app.classList.toggle('sb-collapsed', collapsed);
    btn.textContent = collapsed ? '☰' : '⟨';
    btn.title = (collapsed ? 'Show' : 'Hide') + ' sidebar (Ctrl+B)';
    if(save){ try{ localStorage.setItem(KEY, collapsed ? '1' : '0'); }catch(_){} }
    // Editors / previews measure their width — re-measure once the grid transition ends.
    setTimeout(() => {
      document.querySelectorAll('.CodeMirror').forEach(el => el.CodeMirror && el.CodeMirror.refresh());
      window.dispatchEvent(new Event('resize'));
    }, 280);
  }
  const toggle = () => set(!app.classList.contains('sb-collapsed'), true);
  btn.addEventListener('click', toggle);
  window.addEventListener('keydown', e => {
    if((e.metaKey || e.ctrlKey) && !e.shiftKey && !e.altKey && e.key.toLowerCase() === 'b'){
      e.preventDefault();
      toggle();
    }
  });

  let saved = null;
  try{ saved = localStorage.getItem(KEY); }catch(_){}
  set(saved === '1', false);
})();
