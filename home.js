// Injects a floating "Home" button into any lab page.
// Resolves the index URL from this script's own src, so every lab —
// regardless of folder depth — points to the same main page.
(function () {
  if (window.__apHomeBtnInstalled) return;
  window.__apHomeBtnInstalled = true;

  const me = document.currentScript;
  const homeUrl = me ? new URL('index.html', me.src).href : 'index.html';

  const css = `
    .ap-home-btn{
      position: fixed; top: 14px; right: 14px; z-index: 99999;
      display: inline-flex; align-items: center; gap: 8px;
      padding: 9px 15px;
      font: 600 12.5px/1 'Inter', system-ui, -apple-system, Segoe UI, Roboto, sans-serif;
      color: #e8e8f3; text-decoration: none; letter-spacing: 0.01em;
      background: rgba(18, 18, 32, 0.78);
      border: 1px solid rgba(255,255,255,0.15);
      border-radius: 999px;
      box-shadow:
        0 10px 28px -10px rgba(0,0,0,0.55),
        inset 0 0 0 1px rgba(255,255,255,0.04);
      -webkit-backdrop-filter: blur(14px) saturate(150%);
      backdrop-filter: blur(14px) saturate(150%);
      transition: background .18s, color .18s, border-color .18s, transform .18s, box-shadow .18s;
      cursor: pointer; user-select: none;
    }
    .ap-home-btn:hover{
      background: linear-gradient(135deg, rgba(124,92,255,0.92), rgba(53,208,255,0.85));
      border-color: rgba(255,255,255,0.32);
      color: #fff; transform: translateY(-1px);
      box-shadow:
        0 16px 36px -10px rgba(124,92,255,0.55),
        inset 0 0 0 1px rgba(255,255,255,0.18);
    }
    .ap-home-btn:focus-visible{
      outline: none;
      box-shadow:
        0 0 0 3px rgba(124,92,255,0.45),
        0 16px 36px -10px rgba(124,92,255,0.55);
    }
    .ap-home-btn .ap-home-ico{
      display: inline-flex; align-items: center; justify-content: center;
      width: 20px; height: 20px; font-size: 13px;
      border-radius: 50%;
      background: rgba(255,255,255,0.08);
      transition: background .18s, transform .18s;
    }
    .ap-home-btn:hover .ap-home-ico{
      background: rgba(255,255,255,0.20);
      transform: scale(1.06) rotate(-6deg);
    }
    @media print{ .ap-home-btn{ display:none } }
  `;

  function install() {
    if (document.querySelector('.ap-home-btn')) return;
    const style = document.createElement('style');
    style.textContent = css;
    document.head.appendChild(style);

    const a = document.createElement('a');
    a.className = 'ap-home-btn';
    a.href = homeUrl;
    a.title = 'Back to Advanced Programming home';
    a.setAttribute('aria-label', 'Back to home');
    a.innerHTML = '<span class="ap-home-ico" aria-hidden="true">⌂</span><span>Home</span>';
    document.body.appendChild(a);
  }

  if (document.body) install();
  else document.addEventListener('DOMContentLoaded', install);
})();
