document.addEventListener("DOMContentLoaded", () => {

const checkTextArea = document.getElementById("value");
const infoTextArea = document.getElementById("info");
const sendButton = document.getElementById("send");
const openButton = document.getElementById("open");

const serverIp = "3.23.64.148";
const regExp = /[^(\d+(.\d+)?)]/g;

const EMPTY_STRING = "";
const MIN_WORDS_COUNT = 3;
const MAX_PERCENTAGE = 100;

infoTextArea.disabled = true;

checkTextArea.addEventListener("keyup", (e) => {
  const wordsArray = e.target.value.split(" ").filter( str => str.length > 0 );
  const wordsCounter = wordsArray.length;
  e.preventDefault();

  if (wordsCounter >= MIN_WORDS_COUNT) {
    sendButton.disabled = false;
    sendButton.title = EMPTY_STRING;
    
    if (e.code === "Enter") {
      sendButton.disabled = false;
      sendButton.title = EMPTY_STRING;
      sendButton.click();
    }
  } else {
    sendButton.disabled = true;
    sendButton.title = "Enter at least 3 words!";
  }
});

sendButton.addEventListener("click", async (e) => {
  const payload = "name=" + encodeURIComponent(checkTextArea.value);
  const screenWidth = window.screen.width;
  e.preventDefault();
  try {
    const response = await fetch(`http://${serverIp}:8080/cgi-bin/script.cgi`, {
        method: "POST",
        headers: {"Content-Type": "application/x-www-form-urlencoded"},
        body: payload
    });
    const text = await response.text();
    const answerNumber = MAX_PERCENTAGE - parseInt( text.replace(regExp, EMPTY_STRING) );
    if(screenWidth <= 670){document.querySelector("#image2").style.display = "flex";}
    document.querySelector(".img-main2").classList.add("opacity"); 
    document.querySelector(".img-main").classList.add("opacity");
    document.querySelector("#result").innerHTML = `${answerNumber}% unique`;
    document.querySelector("#result2").innerHTML = `${answerNumber}% unique`;
  } catch (e) {
    throw new Error(e.message);
  }
});

openButton.addEventListener("click", async (e) => {
  infoTextArea.innerText = EMPTY_STRING;
  e.preventDefault();
  try {
    const response = await fetch(`http://${serverIp}:8080/cgi-bin/text.cgi`);
    const text = await response.text();    
    infoTextArea.innerHTML = text;
    infoTextArea.style.color = 'black';
  } catch (e) {
    throw new Error(e.message);
  }
});

window.addEventListener("resize", function() {
  if (window.matchMedia("(min-width: 670px)").matches) {
    document.querySelector("#image2").style.display = "none";
  }
});

});
