import { Link } from "react-router-dom";

const Navbar = () => {
  return (
    <nav style={{ backgroundColor: "#4CAF50", padding: "10px", color: "white" }}>
      <Link to="/" style={{ margin: "0 15px", color: "white", textDecoration: "none" }}>Home</Link>
      <Link to="/about" style={{ margin: "0 15px", color: "white", textDecoration: "none" }}>About</Link>
      <Link to="/contact" style={{ margin: "0 15px", color: "white", textDecoration: "none" }}>Contact</Link>
      <Link to="/user/john" style={{ margin: "0 15px", color: "white", textDecoration: "none" }}>User (Dynamic)</Link>
    </nav>
  );
};

export default Navbar;