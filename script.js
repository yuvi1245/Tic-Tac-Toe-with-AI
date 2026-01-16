let board = ["","","","","","","","",""];
const human = "X";
const ai = "O";
const boardDiv = document.getElementById("board");
const statusText = document.getElementById("status");
const celebration = document.getElementById("celebration");

function createBoard() {
    boardDiv.innerHTML = "";
    board.forEach((cell, i) => {
        const div = document.createElement("div");
        div.className = "cell";
        div.innerText = cell;
        if(cell === "X") div.style.color = "#00d2ff";
        if(cell === "O") div.style.color = "#ff416c";
        div.onclick = () => playerMove(i);
        boardDiv.appendChild(div);
    });
}

function playerMove(i) {
    if (board[i] || checkWinner(board)) return;
    board[i] = human;
    createBoard();
    if (checkResult()) return;

    setTimeout(() => {
        aiMove();
        createBoard();
        checkResult();
    }, 300);
}

function aiMove() {
    let bestScore = -Infinity;
    let move;
    for (let i = 0; i < 9; i++) {
        if (board[i] === "") {
            board[i] = ai;
            let score = minimax(board, false);
            board[i] = "";
            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    board[move] = ai;
}

function minimax(b, isMax) {
    let res = checkWinner(b);
    if (res === "O") return 1;
    if (res === "X") return -1;
    if (res === "tie") return 0;

    if (isMax) {
        let best = -Infinity;
        for (let i = 0; i < 9; i++) {
            if (b[i] === "") { b[i] = ai; best = Math.max(best, minimax(b, false)); b[i] = ""; }
        }
        return best;
    } else {
        let best = Infinity;
        for (let i = 0; i < 9; i++) {
            if (b[i] === "") { b[i] = human; best = Math.min(best, minimax(b, true)); b[i] = ""; }
        }
        return best;
    }
}

function checkWinner(b) {
    const wins = [[0,1,2],[3,4,5],[6,7,8],[0,3,6],[1,4,7],[2,5,8],[0,4,8],[2,4,6]];
    for (let [a, b1, c] of wins) {
        if (b[a] && b[a] === b[b1] && b[a] === b[c]) return b[a];
    }
    return b.includes("") ? null : "tie";
}

function checkResult() {
    let result = checkWinner(board);
    if (!result) return false;

    if (result === "tie") {
        statusText.innerText = "Draw! Restarting...";
        setTimeout(resetGame, 1000);
    } else {
        celebration.innerHTML = result === human ? "🏆<br>YOU WIN!" : "🤖<br>AI WINS!";
        celebration.classList.remove("hidden");
        setTimeout(() => celebration.classList.add("hidden"), 3000);
    }
    return true;
}

function resetGame() {
    board = ["","","","","","","","",""];
    statusText.innerText = "";
    celebration.classList.add("hidden"); 
    createBoard();
}

createBoard();