document.addEventListener('DOMContentLoaded', function() {
    document.querySelector('form').onsubmit = function() {
        document.getElementById('ans').innerHTML=('Hello ' + document.querySelector('#name').value);
        return false;
    };
});



function lightmode(){
        let body = document.querySelector('body');
        document.querySelector('#lightmode').onclick = function() {
            body.style.backgroundColor = 'white';
            document.getElementById('lightmode').onclick = function() {darkmode()};
            document.querySelector('.hello').style.color='black';
            document.getElementById('lightmode').innerHTML="Lightmode on";
            };
        }

function darkmode(){
        let body = document.querySelector('body');
        document.querySelector('#lightmode').onclick = function() {
            document.getElementById('lightmode').onclick = function() {lightmode()};
            body.style.backgroundColor = 'black';
            document.querySelector('.hello').style.color='white';
            document.querySelector('.hello').style.backgroundcolor='grey';
            document.getElementById('lightmode').innerHTML="Lightmode off";
            };
        }
