import { useParams } from "react-router-dom";

const User = () => {
  const { username } = useParams();

  return (
    <div>
      <h1>User Profile</h1>
      <p>Welcome, {username}!</p>
    </div>
  );
};

export default User;
