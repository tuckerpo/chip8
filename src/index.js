document.addEventListener("DOMContentLoaded", function () {
    document.querySelector("#rom").onchange = async (event) => {
        const file = event.target.value;
        const response = await fetch(`./roms/${file}`);
        const arrayBuf = await response.arrayBuffer();
        const gameData = new Uint8Array(arrayBuf);

        const loadrom = Module.cwrap("load_rom", "null", ['array']);
        loadrom(gameData);
    }
});
