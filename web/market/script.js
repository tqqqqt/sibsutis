var itog_sum=0;
var itog_chislo=0;
var el1=document.getElementById('kol');
var el2=document.getElementById('sum');
function sum(object,cena){
    if(object.value=="Купить"){
        itog_sum+=cena;
        itog_chislo+=1;
        el1.innerHTML=itog_chislo;
        el2.innerHTML=itog_sum;
    }
    else alert("Предмет уже куплен")
}
function chen(object){
    object.value="Куплено";
    object.style.background="#64CCED";
}
function hid(){
    if(document.getElementById('c1').checked==true){
        document.getElementById('card1').style.display="none";
    }
    if(document.getElementById('c2').checked==true){
        document.getElementById('card3').style.display="none";
    }
    if(document.getElementById('c3').checked==true){
        document.getElementById('card5').style.display="none";
    }
    if(document.getElementById('c4').checked==true){
        document.getElementById('card7').style.display="none";
    }
    if(document.getElementById('c5').checked==true){
        document.getElementById('card2').style.display="none";
    }
    if(document.getElementById('c6').checked==true){
        document.getElementById('card4').style.display="none";
    }
    if(document.getElementById('c7').checked==true){
        document.getElementById('card6').style.display="none";
    }
    if(document.getElementById('c8').checked==true){
        document.getElementById('card3').style.display="none";
    }
    if(document.getElementById('c9').checked==true){
        document.getElementById('card7').style.display="none";
    }
    if(document.getElementById('c1').checked!=true) document.getElementById('card1').style.display="block";
    if(document.getElementById('c5').checked!=true) document.getElementById('card2').style.display="block";
    if(document.getElementById('c2').checked!=true && document.getElementById('c8').checked!=true) document.getElementById('card3').style.display="block";
    if(document.getElementById('c6').checked!=true) document.getElementById('card4').style.display="block";
    if(document.getElementById('c3').checked!=true) document.getElementById('card5').style.display="block";
    if(document.getElementById('c7').checked!=true) document.getElementById('card6').style.display="block";
    if(document.getElementById('c4').checked!=true && document.getElementById('c9').checked!=true) document.getElementById('card7').style.display="block";
}