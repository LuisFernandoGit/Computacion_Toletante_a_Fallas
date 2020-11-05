//Programa que simula el algoritmo de planificación FCFS (First Come First Served) y
//maneja interrupciones.
#include <iostream>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include <proceso.h>
#include <cola.h">
using namespace std;

void gotoxy(int x, int y)
{ //Declaración de la función gotoxy de C
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

int main()
{
    int max = 0;      //Declaración de la variable que representará el número máximo de procesos.
    int contador = 0; //Declaración del contador que verificará que solo existan 4 procesos en memoria.
                      //    int posicionl = 0;
                      //    int posicionp = 0;
    int idi = 1;      //Declaración de una variable que se irá incrementando y funcionará como el id de cada proceso.
    cout << "Ingrese el numero de procesos que quiere ingresar: ";
    cin >> max;
    cin.ignore();
    while (max > 25)                                                                 //Ya que el máximo de elementos que podemos tener en nuestra cola es de 25,
    {                                                                                //usaremos este ciclo para validar que el programa no avance si los procesos ingresados
        cout << "Demasiados procesos, por favor ingrese una cantidad menor" << endl; // exceden 25.
        cout << "Ingrese el número de procesos que quiere ingresar: ";
        cin >> max;
        cin.ignore();
    }
    system("cls");
    //int val;
    Proceso p;       //Declaración de un objeto tipo proceso al cual le asignaremos todos los valores en sus atributos.
    Cola<Proceso> c; //Declaración de una cola de procesos, donde encolaremos los procesos "p" que vayamos generando.
    //lote l[4];
    for (int i = 1; i <= max; i++) //Este for se repetirá el mismo número de veces que el número de procesos ingresados en max.
    {
        p.id = idi;
        p.op1 = rand() % 30 + 1; //El operando izquierdo es generado aleatoriamente en un rango de 1 a 30.
        p.op2 = rand() % 30 + 1; //Lo mismo con el derecho.
        int op = rand() % 6 + 1; //La operación es generada aleatoriamente en un rango de 1 a 7.
        if (op == 1)             //Dependiendo el número generado, será la operación que se llevará a cabo.
        {
            p.op = 1;                    //Siendo 1 el equivalente a una suma, sumaremos los operandos generados y
            p.resultado = p.op1 + p.op2; //guardaremos el resultado en su respectivo atributo.
        }
        else if (op == 2) //Haremos esto mismo con todas las opciones.
        {
            p.op = 2;
            p.resultado = p.op1 - p.op2;
        }
        else if (op == 3)
        {
            p.op = 3;
            p.resultado = p.op1 * p.op2;
        }
        else if (op == 4)
        {
            p.op = 4;
            p.resultado = p.op1 / p.op2;
        }
        else if (op == 5)
        {
            p.op = 5;
            p.resultado = p.op1 % p.op2;
        }
        else if (op == 6)
        {
            p.op = 6;                        //En caso de 6; que quivale a una potencia, volveremos a generar aleatoriamente
            p.op1 = rand() % 10 + 1;         //los operandos, pero esta vez el operando izquierdo (número base) en un rango de 10
            p.op2 = rand() % 6 + 1;          //y el operando derecho (potencia) en un rango de 6, esto con la finalidad de
            p.resultado = pow(p.op1, p.op2); //evitar que se genere un resultado muy grande.
        }

        p.tiempo = rand() % 16 + 1; //El tiempo estimado del proceso es generado aleatoriamente en un rango de 7 a 16.
        if (p.tiempo < 7)
        {
            p.tiempo = p.tiempo + 7;
        }
        idi++; //Incrementamos nuestra variable que sirve como id autoincrementable.
        c.encolar(p);
        system("cls");
    }
    int pp = max - 4; //Esta variable representa los procesos pendientes que se encuentran en el estado "Nuevo",
    if (pp < 0)       //Como debemos tener 4 procesos en memoria, esta variable será igual al número de procesos
    {
        pp = 0; //ingresados menos 4. Si la resta diera un valor negativo, entonces no quedarían procesos pendientes.
    }
    int cg = 0;      //Declaración del contador global.
    int tt;          //Declaración del tiempo transcurrido.
    int y = 4;       //y será una variable que servirá como la coordenada vertical de la función gotoxy.
    int y1 = 4;      //Otra coordenada vertical para gotoxy.
    int tr;          //Declaración del tiempo restante.
    int teclav;      //Bandera para cambiar el comportamiento del programa dependiendo la interrupción.
    int vacio = 0;   //Bandera para cambiar el comportamiento del programa si no hay procesos activos en memoria.
    int resp;        //Declaración del tiempo de respuesta.
    char tecla;      //Variable que guardará la tecla que hayamos presionado durante la ejecución del algoritmo.
    string operador; //Cadena que nos servirá para imprimir el operador en la operación del proceso.
                     //    posicionl = 0;
                     //    posicionp = 0;
    contador = 0;
    //    lote terminados[4];
    Cola<Proceso> bloqueados; //Creamos una cola para colocar los procesos bloqueados.
    Cola<Proceso> terminados; //Creamos una cola para colocar los procesos terminados.
    Cola<Proceso> activos;    //Creamos una cola para colocar los procesos activos en memoria.
    Proceso nuevo;            //Declaramos un proceso nuevo que nos servirá de auxiliar.

    cout << "Porcesos nuevos: " << pp; //Imprimimos los procesos pendientes
    gotoxy(0, 2);
    cout << "Procesos Listos:";
    gotoxy(0, 3);
    cout << "ID";
    gotoxy(5, 3);
    cout << "TME" << endl;
    gotoxy(11, 3);
    cout << "TT";
    gotoxy(0, 4);
    while (!c.vacia()) //Desencolamos e imprimimos los primeros 4 procesos que estarán activos en memoria.
    {
        gotoxy(0, y1);
        cout << c.frente().id;
        gotoxy(6, y1);
        cout << c.frente().tiempo;
        gotoxy(11, y1);
        cout << c.frente().tt;

        nuevo = c.frente();     //Creamos un proceso nuevo con los datos del proceso actual, ya que no podemos modificar sus atributos desde la cola.
        nuevo.t.llegada = 0;    //Asignamos el tiempo de llegada como 0 debido a que son los primeros en llegar.
        activos.encolar(nuevo); //Encolamo el proceso actual con el tiempo de llegada actualizado.
        c.desencolar();         //Nos movemos al siguiente elemento en la cola.

        y1++;              //Incrementamos y para imprimir los procesos uno debajo del otro.
        contador++;        //Usamos contador para llevar la cuenta de los procesos encolados en memoria.
        if (contador == 4) //El ciclo terminará hasta que se hayan desencolado 4 procesos. Si inicialmente se
        {
            break; //generaron menos de 4, entonces el ciclo terminará cuando la cola quede vacía.
        }
    }
    y1 = 4;       //Reiniciamos el valor de y a 4 para volver a imprimir los procesos en esta posición después.
    contador = 0; //Reiniciamos el contador ya que ahora nos serivirá para otra cosa.
                  //    for(int j = posicionp; j<4; j++)
                  //    {

    gotoxy(20, 2); //Imprimimos espacios donde vamos a mostrar los datos de los procesos en ejecución, terminados y bloqueados.
    cout << "Ejecucion:";
    gotoxy(20, 3);
    cout << "ID: ";
    gotoxy(20, 4);
    cout << "Op: ";
    gotoxy(20, 5);
    cout << "TME: ";
    gotoxy(20, 6);
    cout << "TR: ";
    gotoxy(20, 7);
    cout << "TT: ";

    gotoxy(40, 2);
    cout << "Terminados:";
    gotoxy(40, 3);
    cout << "ID";
    gotoxy(46, 3);
    cout << "Operacion";
    gotoxy(59, 3);
    cout << "Resultado";

    gotoxy(0, 10);
    cout << "Bloqueados:";
    gotoxy(0, 11);
    cout << "ID";
    gotoxy(5, 11);
    cout << "TTB";

    gotoxy(5, 20);
    cout << "Contador Global: " << cg << endl; //Mostramos el contador global, que en estos momentos vale 0
    Sleep(2300);                               //y pausamos el programa por 2.3 segundos.

    while (max > 0) //Este ciclo va a finalizar hasta que todos los procesos ingresados hayan finalizado.
    {               //es decir, cuando max valga 0.
        system("cls");
        gotoxy(5, 21);
        cout << "Tecla presionada: ";                      //Imprimimos el espacio donde vamos a colocar la tecla que se presione durante este ciclo.
        teclav = 0;                                        //Inicializamos nuestra bandera de tecla en 0.
        tt = activos.frente().tt;                          //Tomamos el tiempo transcurrido actual de nuestro proceso al tope de la cola.
        tr = activos.frente().tiempo - tt;                 //Calculamos el tiempo restante restando el tiempo estimado y el tiempo transcurrido.
                                                           //        tt = l[posicionl].proceso[posicionp].tt;
                                                           //        tr = l[posicionl].proceso[posicionp].tiempo - tt;
        cg--;                                              //Decrementamos el contador global para que se sincronice con los tiempos de arriba.
        for (int x = 0; x <= activos.frente().tiempo; x++) //Este ciclo se repetirá el mismo número de veces que el tiempo estimado,
        {                                                  //en otras pabras, hasta que tiempo restante sea 0.
            if (tt == 0 && vacio == 0)                     //Para obtener el tiempo de respuesta, necesitamos calcularlo en la primera
            {
                resp = cg + 1 - activos.frente().t.llegada; //iteración del ciclo; o sea, cuando el proceso pase a ejecución.
            }
            gotoxy(0, 0);
            cout << "Porcesos nuevos: " << pp; //Como uno de los procesos va a moverse de "Listo" a "En ejecución"
            gotoxy(0, 2);                      //necesitamos reimprimir los procesos en "Listo".
            cout << "Procesos Listos:";
            gotoxy(0, 3);
            cout << "ID";
            gotoxy(5, 3);
            cout << "TME" << endl;
            gotoxy(11, 3);
            cout << "TT";
            gotoxy(0, 4);
            Cola<Proceso> aux = activos; //Creamos una cola auxiliar para obtener los datos de los 4 procesos en memoria sin
                                         //desencolarlos de la cola de procesos activos.
            aux.desencolar();            //Desencolamos el proceso en el frente, debido a que este se moverá a "En ejecución".
            while (!aux.vacia())
            {
                gotoxy(0, y1);
                cout << aux.frente().id;
                gotoxy(6, y1);
                cout << aux.frente().tiempo;
                gotoxy(11, y1);
                cout << aux.frente().tt;
                aux.desencolar();
                y1++;
            }
            y1 = 4;

            if (activos.frente().op == 1) //Comparamos el valor de la operación para determinar qué operación es,
            {
                operador = "+"; //de forma similar a como se hizo en la generación de procesos.
            }
            else if (activos.frente().op == 2)
            {
                operador = "-";
            }
            else if (activos.frente().op == 3)
            {
                operador = "*";
            }
            else if (activos.frente().op == 4)
            {
                operador = "/";
            }
            else if (activos.frente().op == 5)
            {
                operador = "R";
            }
            else if (activos.frente().op == 6)
            {
                operador = "^";
            }
            else
            {
                operador = ""; //Si no es ninguno de los valores preestablecidos, entonces no guardaremos nada
            }                  //ya que significa que es un proceso vacío.
            gotoxy(20, 2);
            cout << "Ejecucion:" << endl; //Imprimimos los datos del proceso que acaba de pasar a ejecución.
            gotoxy(20, 3);
            cout << "ID: " << activos.frente().id << endl;
            gotoxy(20, 4);
            cout << "Op: " << activos.frente().op1 << operador << activos.frente().op2;
            gotoxy(20, 5);
            cout << "TME: " << activos.frente().tiempo << endl;
            gotoxy(20, 6);
            cout << "TR: " << tr << " ";
            gotoxy(20, 7);
            cout << "TT: " << tt << " ";
            tr--;                              //En cada iteración se decrementará el tiempo restante.
            tt = activos.frente().tiempo - tr; //En cada iteración se recalculará el tiempo transcurrido.

            gotoxy(40, 2); //Imprimimos los datos de los procesos que ya hayan terminado.
            cout << "Terminados:" << endl;
            gotoxy(40, 3);
            cout << "ID";
            gotoxy(46, 3);
            cout << "Operacion";
            gotoxy(59, 3);
            cout << "Resultado";
            string operadorr; //Otra cadena para guardar el operador de la operación del proceso.

            if (!terminados.vacia())
            {                     //Usamos la cola auxiliar nuevamente, para imprimir los datos de los procesos terminados
                aux = terminados; //sin desencolarlos de la cola de terminados.
                while (!aux.vacia())
                {
                    if (aux.frente().op == 1) //El proceso de determinar la operación es el mismo.
                    {
                        operadorr = "+";
                    }
                    else if (aux.frente().op == 2)
                    {
                        operadorr = "-";
                    }
                    else if (aux.frente().op == 3)
                    {
                        operadorr = "*";
                    }
                    else if (aux.frente().op == 4)
                    {
                        operadorr = "/";
                    }
                    else if (aux.frente().op == 5)
                    {
                        operadorr = "R";
                    }
                    else if (aux.frente().op == 6)
                    {
                        operadorr = "^";
                    }
                    gotoxy(40, y);
                    cout << aux.frente().id;
                    gotoxy(46, y);
                    cout << aux.frente().op1 << operadorr << aux.frente().op2;
                    gotoxy(59, y);
                    if (aux.frente().resultado == -3000)
                    {
                        cout << "Error"; //Imprimiremos un error en el resultado es -3000, es decir
                    }                    //si el proceso terminó con la tecla w.
                    else
                    {
                        cout << aux.frente().resultado; //Si el proceso terminó normalmente, imprimimos el resultado de la operación.
                    }
                    aux.desencolar();
                    y++;
                }
            }
            y = 4;

            gotoxy(0, 10); //Imprimimos los datos de los procesos bloqueados.
            cout << "Bloqueados:";
            gotoxy(0, 11);
            cout << "ID";
            gotoxy(5, 11);
            cout << "TTB";
            gotoxy(0, 12);
            cout << "               "; //Imprimimos espacios en blanco para limpiar los datos de esta sección
            gotoxy(0, 13);             //sin limpiar toda la pantalla.
            cout << "               ";
            gotoxy(0, 14);
            cout << "               ";
            gotoxy(0, 15);
            cout << "               ";

            int y3 = 12; //Necesitaremos una tercera coordenada verical para imprimir los procesos bloqueados sin afectar las posiciones de las demás secciones.
            while (!bloqueados.vacia())
            {
                gotoxy(0, y3);
                cout << bloqueados.frente().id;
                gotoxy(6, y3);
                cout << bloqueados.frente().ttb;
                y3++;

                nuevo = bloqueados.frente();
                nuevo.ttb++; //Aumentamos el tiempo trancurrido en bloqueado en cada iteración del for.

                if (nuevo.ttb <= 7) //Usaremos la cola auxiliar para guardar los procesos bloqueados con el TTB actualizado
                {
                    aux.encolar(nuevo); //ya que necesitamos desencolar todos los procesos bloqueados para imprimirlos.
                }
                else //Una vez hayan pasado 7 iteraciones el proceso pasará de "Bloqueado" a "Listo".
                {
                    nuevo.ttb = 0;          //Reiniciamos el TTB a 0 para volverlo a usar en caso de que el proceso fuera bloqueado otra vez.
                    activos.encolar(nuevo); //Encolamos el proceso bloqueado a la cola de procesos en memoria.
                    if (vacio == 1)         //Si la bandera de proceso vacío está activa entonces terminaremos el proceso.
                    {
                        vacio = 0;  //Reiniciamos la bandera.
                        tr = -1;    //Rompemos el ciclo
                        teclav = 1; //Activamos esta bandera desencolar el proceso vacío después de salir del ciclo.
                    }
                }
                bloqueados.desencolar();
            }
            while (!aux.vacia()) //Regresamos los procesos que guardamos en aux a la cola de bloqueados.
            {
                bloqueados.encolar(aux.frente());
                aux.desencolar();
            }

            gotoxy(5, 20);
            cg++; //Incrementamos el contador global.
            cout << "Contador Global: " << cg << endl;
            Sleep(1000); //En cada iteración pausamos el programa un segundo, para simular los tiempos de los procesos.
                         //De forma más simple, cada iteración es un segundo transurrido en el programa.
            if (kbhit())
            {
                tecla = getch(); //Si se presionó una tecla, entonces la guardaremos aquí.
                gotoxy(5, 21);
                cout << "Tecla presionada: " << tecla;
                //Las e p y w activarán interrupciones en el programa.
                if (tecla == 'e' && vacio == 0) //Aparte de comparar la tecla que se presionó debemos comparar que no haya un
                {                               //proceso vacío en ejecución. Si hubiese uno entonces no deberíamos ser capaces de usar estas interrupciones.
                    while (!bloqueados.vacia()) //La tecla e es la que mandará a nuestro proceso en ejecución a bloqueado.
                    {
                        nuevo = bloqueados.frente();
                        nuevo.ttb--; //Decrementamos el TTB de los proceso que ya estén bloqueados para sincronizarlo
                                     //con los otros tiempos.
                        aux.encolar(nuevo);
                        bloqueados.desencolar();
                    }
                    while (!aux.vacia()) //Repetimos el proceso de guardar los bloqueados en la cola auxiliar y
                    {                    //después regresarlos a la cola de bloqueados.
                        bloqueados.encolar(aux.frente());
                        aux.desencolar();
                    }

                    nuevo = activos.frente();    //Guardaremos el tiempo transcurrido en el proceso para usarlo cuando regrese a ejecución.
                    nuevo.tt = tt - 1;           //Restamos uno al TT ya que al final de la iteración este se incrementa,
                                                 //por lo que si pasan 10 iteraciones entonces el TT diría que pasaron 11.
                    if (nuevo.t.respuesta == -1) //Verificamos que el tiempo de respuesta no se haya asignado aún.
                    {
                        nuevo.t.respuesta = resp; //Si no se ha asignado, entonces lo hacemos aquí.
                    }
                    bloqueados.encolar(nuevo); //Encolamos el proceso en ejecuión actual a la cola de bloqueados.
                    Sleep(1000);               //Pausamos un segundo para que se pueda apreciar la tecla que se presionó antes de limpiar la pantalla.
                    tr = -1;                   //rompemos el ciclo.
                    teclav = 1;                //Activamos la bandera.
                }

                else if (tecla == 'p')   //La tecla p pausará el programa.
                {                        //Entramos en un ciclo infinito, que no se romperá hasta que se presione la
                    while (tecla != 'c') //la tecla c, para simular que el programa fue pausado.
                    {
                        if (kbhit())
                        {
                            tecla = getch();
                            gotoxy(5, 21);
                            cout << "Tecla presionada: " << tecla;
                        }
                    }
                }

                else if (tecla == 'w' && vacio == 0) //La tecla w forzará que el proceso en ejecución termine con un error.
                {
                    Sleep(1000); //Pausamos un segundo para que se pueda apreciar la tecla que se presionó antes de limpiar la pantalla.
                    teclav = 2;  //Activamos la bandera.
                    tr = -1;     //rompemos el ciclo.
                }
            }

            if (tr < 0)                      //Para romper el ciclo, hacemos que el tiempo restante valga -1, de esa forma entraremos en
            {                                //esta condición que hará que el contador del for sea igual al tiempo estimado, lo cual
                x = activos.frente().tiempo; //terminará el ciclo.
                //x = l[posicionl].proceso[posicionp].tiempo;
            }
        }

        if (teclav != 1) //Si la bandera de tecla no vale 1, entonces significa que el proceso terminó.
        {
            nuevo = activos.frente(); //Creamos un proceso nuevo con los datos del proceso actual para asignarle los tiempos.
            if (teclav == 2)          //Si la bandera vale 2 quiere decir que se presionó la tecla w.
            {
                nuevo.resultado = -3000; //Asignamos como resultado a -3000 para representarlo como un error a la hora de imprimirlo.
                teclav = 0;              //Reiniciamos la bandera.
            }
            nuevo.t.finalizacion = cg; //Calculamos los tiempos del proceso.
            nuevo.t.servicio = tt - 1;
            nuevo.t.retorno = nuevo.t.finalizacion - nuevo.t.llegada;
            nuevo.t.espera = nuevo.t.retorno - nuevo.t.servicio;
            if (nuevo.t.respuesta == -1) //Verificamos que el tiempo de respuesta no se haya asignado aún.
            {
                nuevo.t.respuesta = resp; //Si no se ha asigando, entonces lo asignamos aquí.
            }
            terminados.encolar(nuevo); //Encolamos el proceso a la cola de terminados.
            activos.desencolar();      //Sacamos el proceso de memoria.
            if (activos.vacia())       //Si no queda ningún proceso en "Listo" pero aún quedan procesos pendientes
            {                          //entonces insertaremos un proceso vacío. Un proceso vacío solo tendrá como función
                Proceso v;             //hacer que el tiempo siga transcurriendo mientras llega un nuevo proceso a "Listo".
                activos.encolar(v);
                vacio = 1; //Activamos la bandera de proceso vacío.
            }
            if (!c.vacia()) //Al terminar un proceso significa que se liberó un espacio en memoria, así que
            {               //insertaremos un proceso pendiente a los procesos listos.
                nuevo = c.frente();
                nuevo.t.llegada = cg; //El tiempo en el que este proceso va a llegar a memoria es igual a lo que tenemos en nuestro contador global.
                activos.encolar(nuevo);
                c.desencolar();
            }
            if (pp > 0)
            {
                pp--; //Ya que insertamos un proceso pendiente a memoria, reducimos el contador de procesos pendiente.
            }
            max--; //Reducimos el contador de procesos totales ya que a terminó uno.
        }
        else //Si la bandera de tecla vale 1, significa que se presionó la tecla e.
        {
            activos.desencolar(); //Desencolamos el proceso actual, el cual ya habíamos encolado a la cola de bloqueados.
            if (activos.vacia())  //Si todos los procesos están bloqueados entonces tendremos que insertar un proceso vacío.
            {
                Proceso v;
                activos.encolar(v);
                vacio = 1;
            }
        }

        gotoxy(0, 24); //colocamos el cursor en una posición donde no estorbe.
    }

    system("cls"); //Nuevamente imprimimos los espacios para mostrar los datos.
    gotoxy(0, 0);  //Ninguno tendrá datos más que "terminados" ya que todos los procesos han finalizado.
    cout << "Porcesos nuevos: " << pp;
    gotoxy(0, 2);
    cout << "Procesos Listos:";
    gotoxy(0, 3);
    cout << "ID";
    gotoxy(5, 3);
    cout << "TME" << endl;
    gotoxy(11, 3);
    cout << "TT";
    gotoxy(0, 4);

    gotoxy(20, 2);
    cout << "Ejecucion:";
    gotoxy(20, 3);
    cout << "ID: ";
    gotoxy(20, 4);
    cout << "Op: ";
    gotoxy(20, 5);
    cout << "TME: ";
    gotoxy(20, 6);
    cout << "TR: ";
    gotoxy(20, 7);
    cout << "TT: ";

    gotoxy(40, 2);
    cout << "Terminados:";
    gotoxy(40, 3);
    cout << "ID";
    gotoxy(46, 3);
    cout << "Operacion";
    gotoxy(59, 3);
    cout << "Resultado";
    string operadorr;

    Cola<Proceso> aux = terminados; //Usamos la cola auxiliar para imprimir los procesos terminados sin perderlos
                                    //ya que necesitaremos imprimirlos nuevamente cuando mostremos los tiempos.
    while (!terminados.vacia())
    {
        if (terminados.frente().op == 1)
        {
            operadorr = "+";
        }
        else if (terminados.frente().op == 2)
        {
            operadorr = "-";
        }
        else if (terminados.frente().op == 3)
        {
            operadorr = "*";
        }
        else if (terminados.frente().op == 4)
        {
            operadorr = "/";
        }
        else if (terminados.frente().op == 5)
        {
            operadorr = "R";
        }
        else if (terminados.frente().op == 6)
        {
            operadorr = "^";
        }

        gotoxy(40, y);
        cout << terminados.frente().id;
        gotoxy(46, y);
        cout << terminados.frente().op1 << operadorr << terminados.frente().op2;
        gotoxy(59, y);
        if (terminados.frente().resultado == -3000)
        {
            cout << "Error";
        }
        else
        {
            cout << terminados.frente().resultado;
        }
        terminados.desencolar();
        y++;
    }
    y = 4;

    gotoxy(0, 10);
    cout << "Bloqueados:";
    gotoxy(0, 11);
    cout << "ID";
    gotoxy(5, 11);
    cout << "TTB";

    gotoxy(5, 20);
    cout << "Contador Global: " << cg << endl;
    system("pause"); //Pausamos el programa antes de proceder con la impresión de los tiempos.

    system("cls"); //Imprimimos los tiempos.
    gotoxy(0, 0);
    cout << "ID";
    gotoxy(5, 0);
    cout << "Operacion";
    gotoxy(17, 0);
    cout << "Resultado";
    gotoxy(29, 0);
    cout << "TME";
    gotoxy(35, 0);
    cout << "TLLEG";
    gotoxy(42, 0);
    cout << "TFIN";
    gotoxy(48, 0);
    cout << "TESP";
    gotoxy(54, 0);
    cout << "TSER";
    gotoxy(60, 0);
    cout << "TRET";
    gotoxy(66, 0);
    cout << "TRESP";
    y = 1;

    while (!aux.vacia())
    {
        if (aux.frente().op == 1)
        {
            operadorr = "+";
        }
        else if (aux.frente().op == 2)
        {
            operadorr = "-";
        }
        else if (aux.frente().op == 3)
        {
            operadorr = "*";
        }
        else if (aux.frente().op == 4)
        {
            operadorr = "/";
        }
        else if (aux.frente().op == 5)
        {
            operadorr = "R";
        }
        else if (aux.frente().op == 6)
        {
            operadorr = "^";
        }
        gotoxy(0, y);
        cout << aux.frente().id;
        gotoxy(5, y);
        cout << aux.frente().op1 << operadorr << aux.frente().op2;
        gotoxy(17, y);
        if (aux.frente().resultado == -3000)
        {
            cout << "Error";
        }
        else
        {
            cout << aux.frente().resultado;
        }
        gotoxy(29, y);
        cout << aux.frente().tiempo;
        gotoxy(35, y);
        cout << aux.frente().t.llegada;
        gotoxy(42, y);
        cout << aux.frente().t.finalizacion;
        gotoxy(48, y);
        cout << aux.frente().t.espera;
        gotoxy(54, y);
        cout << aux.frente().t.servicio;
        gotoxy(60, y);
        cout << aux.frente().t.retorno;
        gotoxy(66, y);
        cout << aux.frente().t.respuesta;
        y++;
        aux.desencolar();
    }

    gotoxy(0, 21); //Nuevamente ponemos el cursor donde no estorbe.
    system("Pause");
}
