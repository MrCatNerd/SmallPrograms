let number = random(0, 100);
updateThingy();

function random(min, max){
    return Math.floor(Math.random() * (max-min+1)) + min;
}

function changeColor(color) {
    document.getElementById("Number").style.color = color;
}

function updateThingy() {
    document.getElementById("Number").textContent = number;

    if (number < 10){ // order matters
        changeColor("red");
    }
    else if (number < 0){
        changeColor("orange");
    }
    else if (number > 20){
        changeColor("yellow");
    }
    else if (number > 10){
        changeColor("blue");
    }
    else{
        changeColor("red"); // default color
    }
}

document.getElementById("Plus").addEventListener("click", function() {
    number++;
    updateThingy();
});

document.getElementById("Minus").addEventListener("click", function() {
    number--;
    updateThingy();
});

document.getElementById("Restart").addEventListener("click", function() {
    number = 0;
    updateThingy();
});

