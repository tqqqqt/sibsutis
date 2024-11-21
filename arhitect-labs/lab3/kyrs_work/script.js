let sum2=0;
var summa=0;
var kolvo=0;

function hid(){ // 1 4 6 7
    if(document.getElementById('f1').checked==true){
        document.getElementById('c1').style.display="none"
        document.getElementById('c4').style.display="none"
        document.getElementById('c6').style.display="none"
        document.getElementById('c7').style.display="none"
        document.getElementById('c9').style.display="none"
        document.getElementById('c10').style.display="none"
        document.getElementById('c11').style.display="none"
    }
    else{
        document.getElementById('c1').style.display="block"
        document.getElementById('c4').style.display="block"
        document.getElementById('c6').style.display="block"
        document.getElementById('c7').style.display="block"
        if(document.getElementById('f2').checked!=true){
            document.getElementById('c9').style.display="block"
            document.getElementById('c10').style.display="block"
            document.getElementById('c11').style.display="block"
        }
    }
    if(document.getElementById('f2').checked==true){
        document.getElementById('c2').style.display="none"
        document.getElementById('c3').style.display="none"
        document.getElementById('c5').style.display="none"
        document.getElementById('c8').style.display="none"
        document.getElementById('c9').style.display="none"
        document.getElementById('c10').style.display="none"
        document.getElementById('c11').style.display="none"
    }
    else{
        document.getElementById('c2').style.display="block"
        document.getElementById('c3').style.display="block"
        document.getElementById('c5').style.display="block"
        document.getElementById('c8').style.display="block"
        if(document.getElementById('f1').checked!=true){
            document.getElementById('c9').style.display="block"
            document.getElementById('c10').style.display="block"
            document.getElementById('c11').style.display="block"
        }
    }
    if(document.getElementById('f1').checked==true && document.getElementById('f2').checked==true){
        document.getElementById('c9').style.display="block"
        document.getElementById('c10').style.display="block"
        document.getElementById('c11').style.display="block"
    }
}

function su(id,cena){
    if(id.checked==true){
        summa+=cena;
        kolvo+=1;
    }
    else if(id.checked!=true){
        summa-=cena;
        kolvo-=1;
    }
    document.getElementById('sum').innerHTML=summa;
    document.getElementById('kol').innerHTML=kolvo;
}

function fu(id1, id2){
    var temp;
    temp = id1.src;
    id1.src=id2.src;
    id2.src=temp;
}

function but(id, cen){
    sum2+=cen;
    id.value="Добавить";
    id.style.border="0px solid black";
    document.getElementById('summ').innerHTML=sum2;
}

function check(id,vari){
    if(vari==2) if(sum2>0){
        id.href="buy_page.html"
    }
    if(vari==1) if(summa>0){
        id.href="buy_page.html"
        id.target="alll"
    }
}

function ran_zak(){
    var i=Math.floor(Math.random()*4995494)
    document.getElementById('zak').innerHTML=i;
}