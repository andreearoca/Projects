import {useState, useEffect} from "react";

const Students = () => {
    const [students, setStudents] = useState([]);
    useEffect(() => {
        fetch('http://localhost:3001/getStudents')
            .then((response) => response.json())
            .then((data) => {
                console.log(JSON.stringify(data.response));
                setStudents(data.response);
                //console.log(resp)
            });

        //event.preventDefault();
    }, [setStudents]);
    if (students.length > 0) {

    }
    return (
      <div>
              <>
                  <h2>All students</h2>
                  <table>
                          <tr>
                              <th>Name</th>
                              <th>Course</th>
                              <th>Grade</th>
                          </tr>
                      {students.map((student) => (
                          <tr key={student._id} className="student">
                              <td>
                                  {student.name}
                              </td>
                              <td>
                                  {student.course}
                              </td>
                              <td>
                                  {student.grade}
                              </td>
                          </tr>
                      ))}
                  </table>
              </>

      </div>
    );
}

export default Students;