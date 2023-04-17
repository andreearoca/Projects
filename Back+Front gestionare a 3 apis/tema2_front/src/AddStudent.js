import {useState} from "react";

const AddStudent = () => {
    const [name, setName] = useState("");
    const [course, setCourse] = useState("");
    const [grade, setGrade] = useState("");
    const [resp, setResp] = useState("response from api")
    const onNameChange = e => setName(e.target.value);
    const onCourseChange = e => setCourse(e.target.value);
    const onGradeChange = e => setGrade(e.target.value);


    const handleSubmit = (event) => {
        //alert('A form was submitted: ' + JSON.stringify(name) + JSON.stringify(course) + JSON.stringify(grade));
        const state = {name: name, course: course, grade: parseInt(grade)};
        fetch('http://localhost:3001/addStudent', {
            method: 'POST',
            headers: { 'content-type': 'application/json' },
            body: JSON.stringify(state)
        }).then((response) => response.json())
            .then((data) => {
                console.log(data.response)
                setResp(data.response)
                console.log(resp)
            });

        event.preventDefault();
    }

    return (
        <form onSubmit={handleSubmit}>
            <h2>
                Add Student
            </h2>
            <div>
                <p>
                    Student Name:
                    <input type="text" value={name} name="name" onChange={onNameChange} />
                </p>
            </div>
            <div>
                <p>
                    Course:
                    <input type="text" value={course} name="course" onChange={onCourseChange} />
                </p>
            </div>
            <div>
                <p>
                    Grade:
                    <input type="text" value={grade} name="grade" onChange={onGradeChange} />
                </p>
            </div>
            <input type="submit" value="Add" />
            <p>
                Response: {resp}
            </p>
        </form>

    );
}

export default AddStudent;