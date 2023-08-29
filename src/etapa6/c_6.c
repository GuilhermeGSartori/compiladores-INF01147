int main() {
    int a = 20;
    int b = 30;

    if(a && b) {
        a = 22;
        a = 33;
    }

    if(a != 4) {
        a = 5;
        a = 6;
    }

    if(a > 7) { // traduzir isso direto pra o assembly.. sem meio termos e tals.. aqueles de analisar o resultado e tranformar em true e false sla.. ignorar
        a = 8;  // tudo eh mto parecido, ver como fica no ILOC, só adaptar o if em si
        a = 9;
    }

    if(a < 10) {
        a = 11;
        a = 12;
    }

    if(a >= 13) {
        a = 14;
        a = 15;
    }

    if(a <= 16) {
        a = 17;
        a = 18;
    }

    if(a == 19) {
        a = 20;
        a = 21;
    }
    else {
        a = 22;
        a = 23;
    }
}