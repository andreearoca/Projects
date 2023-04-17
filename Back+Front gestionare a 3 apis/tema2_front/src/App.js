import React from "react";
import './App.css';
import Translate from "./Translate";
import Students from "./Students";
import AddStudent from "./AddStudent";
import Weather from "./Weather";

function App() {
  return (
      <div>
        <Translate />
          <Students />
          <AddStudent />
          <Weather />
      </div>
  );
}

export default App;
