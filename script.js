let board = ["", "", "", "", "", "", "", "", ""];
let currentPlayer = "X";
let gameActive = true;

const boardDiv = document.getElementById("board");
const statusText = document.getElementById("status");
const celebration = document.getElementById("celebration");
const gameMode = document.getElementById("gameMode");
const difficulty = document.getElementById("difficulty");

function createBoard() {
    boardDiv.innerHTML = "";
    board.forEach((cell, i) => {
        const div = document.createElement("div");
        div.className = "cell";
        div.innerText = cell;
        div.style.color = cell === "X" ? "#00d2ff" : "#ff416c";
        div.onclick = () => handleMove(i);
        boardDiv.appendChild(div);
    });
}

function handleMove(i) {
    if (board[i] !== "" || !gameActive) return;
    board[i] = currentPlayer;
    createBoard();

    if (checkResult(currentPlayer)) return;

    if (gameMode.value === "ai") {
        gameActive = false;
        setTimeout(aiTurn, 500);
    } else {
        currentPlayer = currentPlayer === "X" ? "O" : "X";
    }
}

function aiTurn() {
    let move;
    const diff = difficulty.value;
    if (diff === "easy") move = getRandomMove();
    else if (diff === "medium") move = getMediumMove();
    else move = getBestMove();

    board[move] = "O";
    createBoard();
    if (!checkResult("O")) {
        gameActive = true;
        currentPlayer = "X";
    }
}

function checkResult(p) {
    const wins = [[0,1,2],[3,4,5],[6,7,8],[0,3,6],[1,4,7],[2,5,8],[0,4,8],[2,4,6]];
    const hasWon = wins.some(combo => combo.every(idx => board[idx] === p));
    
    if (hasWon) {
        endGame(p);
        return true;
    }
    if (!board.includes("")) {
        endGame("tie");
        return true;
    }
    return false;
}

function endGame(res) {
    gameActive = false;
    if (res === "tie") {
        statusText.innerText = "It's a Draw!";
    } else {
        celebration.innerHTML = res === "X" ? "🏆 YOU WIN!" : "🤖 AI WINS!";
        celebration.classList.remove("hidden");
    }
}

// AI Logic: Easy, Medium, Hard
function getRandomMove() {
    const avail = board.map((v, i) => v === "" ? i : null).filter(v => v !== null);
    return avail[Math.floor(Math.random() * avail.length)];
}

function getMediumMove() {
    for(let p of ["O", "X"]) { // Win then Block
        for(let i=0; i<9; i++) {
            if(board[i]==="") {
                board[i]=p;
                let wins = [[0,1,2],[3,4,5],[6,7,8],[0,3,6],[1,4,7],[2,5,8],[0,4,8],[2,4,6]];
                let won = wins.some(c => c.every(idx => board[idx] === p));
                board[i]=""; if(won) return i;
            }
        }
    }
    return board[4] === "" ? 4 : getRandomMove();
}

function getBestMove() {
    let bestScore = -Infinity; let move;
    for (let i = 0; i < 9; i++) {
        if (board[i] === "") {
            board[i] = "O";
            let score = minimax(board, false);
            board[i] = "";
            if (score > bestScore) { bestScore = score; move = i; }
        }
    }
    return move;
}

function minimax(b, isMax) {
    const wins = [[0,1,2],[3,4,5],[6,7,8],[0,3,6],[1,4,7],[2,5,8],[0,4,8],[2,4,6]];
    if (wins.some(c => c.every(idx => b[idx] === "O"))) return 1;
    if (wins.some(c => c.every(idx => b[idx] === "X"))) return -1;
    if (!b.includes("")) return 0;

    if (isMax) {
        let best = -Infinity;
        for (let i=0; i<9; i++) if(b[i]==="") { b[i]="O"; best = Math.max(best, minimax(b, false)); b[i]=""; }
        return best;
    } else {
        let best = Infinity;
        for (let i=0; i<9; i++) if(b[i]==="") { b[i]="X"; best = Math.min(best, minimax(b, true)); b[i]=""; }
        return best;
    }
}

function resetGame() {
    board = ["", "", "", "", "", "", "", "", ""];
    currentPlayer = "X"; gameActive = true;
    statusText.innerText = ""; celebration.classList.add("hidden");
    createBoard();
}

function closeCelebration() { celebration.classList.add("hidden"); resetGame(); }
createBoard();