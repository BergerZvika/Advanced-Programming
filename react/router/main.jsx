import React from "react";
import ReactDOM from "react-dom/client";
import { BrowserRouter, Routes, Route } from "react-router-dom"; // npm i -D react-router-dom@latest
import Home from "./pages/Home";
import Navbar from "./pages/Navbar";
import Contact from "./pages/Contact";
import User from "./pages/User";
import About from "./pages/About";
import NotFound from "./pages/NotFound";


export default function App() {
  return (
    <BrowserRouter>
    <Navbar />
    <Routes>
          <Route index element={<Home />} />
          <Route path="/about" element={<About />} />
          <Route path="/contact" element={<Contact />} />
          <Route path="/user/:username" element={<User />} />
          <Route path="*" element={<NotFound />} /> {/* 404 Page */}
      </Routes>
    </BrowserRouter>
  );
}

const root = ReactDOM.createRoot(document.getElementById("root"));
root.render(<App />);
