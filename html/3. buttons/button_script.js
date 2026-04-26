let cliked = false
function changeColor() {
    if (!cliked) {
        document.body.style.backgroundColor = "lightblue"
        cliked = true
    } else {
            document.body.style.backgroundColor = "white"
            cliked = false
    }
}