import {useState} from 'react'

const Translate = () => {
    const [q, setQ] = useState("");
    const [target, setTarget] = useState("");
    const [source, setSource] = useState("");
    const [resp, setResp] = useState("text to be printed")
    const onQChange = e => setQ(e.target.value);
    const onTargetChange = e => setTarget(e.target.value);
    const onSourceChange = e => setSource(e.target.value);


    const handleSubmit = (event) => {
        // alert('A form was submitted: ' + JSON.stringify(this.state));
        const state = {q: q, target: target, source: source};
        fetch('http://localhost:3001/translate', {
            method: 'POST',
            headers: { 'content-type': 'application/json' },
            body: JSON.stringify(state)
        }).then((response) => response.json())
            .then((data) => {
                console.log(JSON.stringify(JSON.parse(data.response).data.translations[0].translatedText))
                setResp(JSON.parse(data.response).data.translations[0].translatedText)
                console.log(resp)
            });

        event.preventDefault();
    }

    return (
        <form onSubmit={handleSubmit}>
            <h2>
                Translate
            </h2>
            <div>
            <p>
                Text To Translate:
                <input type="text" value={q} name="q" onChange={onQChange} />
            </p>
            </div>
            <div>
            <p>
                Language:
                <input type="text" value={source} name="source" onChange={onSourceChange} />
            </p>
            </div>
            <div>
            <p>
                Language To Translate:
                <input type="text" value={target} name="target" onChange={onTargetChange} />
            </p>
            </div>
            <input type="submit" value="Translate" />
            <p>
                Translated text: {resp}
            </p>
        </form>

    );

}

export default Translate;