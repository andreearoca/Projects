import {useState} from "react";

const Weather = () => {
    const [q, setQ] = useState("");
    const [resp, setResp] = useState("Weather will be here")
    const onQChange = e => setQ(e.target.value);


    const handleSubmit = (event) => {
        //alert('A form was submitted: ' + JSON.stringify(q));
        const state = { q: q };
        fetch('http://localhost:3001/weather', {
            method: 'POST',
            headers: { 'content-type': 'application/json' },
            body: JSON.stringify(state)
        }).then((response) => response.json())
            .then((data) => {
                console.log(JSON.stringify(JSON.parse(data.response).current.temp_c))
                setResp(JSON.stringify(JSON.parse(data.response).current.temp_c))
                console.log(resp)
            });

        event.preventDefault();
    }

    return (
        <form onSubmit={handleSubmit}>
            <h2>
                Weather
            </h2>
            <div>
                <p>
                    City:
                    <input type="text" value={q} name="q" onChange={onQChange} />
                </p>
            </div>
            <input type="submit" value="Search" />
            <p>
                Weather in Celsius: {resp}°
            </p>
        </form>

    );
}

export default Weather;