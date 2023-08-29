int a, b, c;
int d;

int main() {
    a = 4;
    d = 1;
    b = d;
    c = a - b; // se comenta isso nao da seg fault... whataheeeeel
    return c;
}
