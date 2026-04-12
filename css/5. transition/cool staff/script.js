// Toggle Dark Mode
document.getElementById("toggle-dark").onclick = () => {
  document.body.classList.toggle("dark");
};

// Lightbox logic
function openLightbox(img) {
  const lightbox = document.getElementById("lightbox");
  const lightboxImg = document.getElementById("lightbox-img");
  lightboxImg.src = img.src;
  lightbox.style.display = "flex";
}

function closeLightbox() {
  document.getElementById("lightbox").style.display = "none";
}
