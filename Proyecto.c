//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
//Funciones del administrador
void administrador();
void añadirUsuario();
void añadirProducto();
void modificarProducto();
void eliminarProducto();
void modificarUsuario();
void eliminarUsuario();
void modificarDineroUsuario();
void modificarCostaProducto();
//Funciones de usuario
void menuCliente(char usuario[], float dineroDisponible);
void usuario();
void comprarProducto(char usuario[], float *dineroDisponible);
void guardarDineroUsuario(char usuario[], float dineroNuevo);
void generarTicket(char usuario[], char producto[], int cantidad, float precioUnitario, float total);
int totalCompra();
int agregarProducto();
void mostrarProductos();
//cupones
void agregarCupon();
float usarCupon(float total);


//Variables globales
int opcion;
//variables struct
//MENU PRINCIPAL
int main(){
    do{
    printf("________________________________ \n");
    printf("║       WHISKERPETS            ║ \n");
    printf(" \n");
    printf("           /\\___/\\\n");
    printf("          (  o o  )\n");
    printf("          /   ^   \\\n");
    printf("         /  |   |  \\\n");
    printf("        (   |___|   )\n");
    printf("         \\__|   |__/\n");
    printf("1. Administrador\n");
    printf("2. compra\n");
    printf("3.-Conatactar programador\n");
    printf("4.-Salir\n");
    printf("Seleccione una opcion: ");
    scanf("%d",&opcion);
        switch(opcion){
            case 1:
                administrador();
                break;
            case 2:
                usuario();
                break;
            case 3:
                printf("Contacte al programador al correo: ");
        }
    } while(opcion!=4);
    
    return 0;
}

//AQUI ESTA LA FUNCION DE ADMINISTRADOR MARIO

void administrador() {
    char user[30], pass[30];
    char archivoUser[30], archivoPass[30];
    int intentos = 0;
    FILE *f;

    //SE ABRE EL ARCHIVO DE ADMINISTRADOR 
    
    f = fopen("admin.txt", "r");
    if(f == NULL){
        printf("ERROR: No se encontro el archivo admin.txt\n");
        return;
    }

    // Leemos usuario y contraseña correctos desde el archivo
    fscanf(f, "%s", archivoUser);
    fscanf(f, "%s", archivoPass);
    fclose(f);

    // Pedir usuario y contraseña hasta 3 intentos
    do {
        printf("\n--- Inicio Administrador ---\n");
        printf("Usuario: ");
        scanf("%s", user);
        printf("Contrasena: ");
        scanf("%s", pass);

        if(strcmp(user, archivoUser) == 0 && strcmp(pass, archivoPass) == 0) {
            printf("\n✔ Acceso concedido.\n");
            break;
        } else {
            printf("\n Usuario o contrasena incorrectos.\n");
            intentos++;
        }

        if(intentos == 3) {
            printf("\nRegresando al menú principal...\n");
            return;
        }

    } while(intentos < 3);

    // Menú administrador
    int opc;
    do {
        printf("\n----- MENU ADMIN  -----\n");
        printf(" /\\_/\\\n");
        printf("( [o.o] )\n");
        printf("  > ^ <\n");
        printf("1. Añadir Usuario\n");
        printf("2. Modificar Usuario\n");
        printf("3. Eliminar Usuario\n");
        printf("4. Añadir Producto\n");
        printf("5. Modificar Producto\n");
        printf("6. Eliminar Producto\n");
        printf("7. Modificar Dinero de Usuario\n");
        printf("8. Modificar Costo de Producto\n");
        printf("9.- Agregar cupon de descuento\n");
        printf("10. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opc);

        switch(opc){
            case 1: añadirUsuario(); break;
            case 2: modificarUsuario(); break;
            case 3: eliminarUsuario(); break;
            case 4: añadirProducto(); break;
            case 5: modificarProducto(); break;
            case 6: eliminarProducto(); break;
            case 7: modificarDineroUsuario(); break;
            case 8: modificarCostaProducto(); break;
            case 9:
            agregarCupon();
            break;
            case 10: printf("Saliendo del administrador...\n"); break;
            default: printf("Opción no valida.\n");
        }

    } while(opc != 10);
}

//AQUI ESTA LA FUNCION PARA AÑADIR EL USUSARIO

void añadirUsuario() {
    FILE *f;
    char user[30], pass[30];
    float dinero;

    printf("\n--- Añadir Nuevo Usuario ---\n");
    printf("Usuario nuevo: ");
    scanf("%s", user);
    printf("Contraseña: ");
    scanf("%s", pass);
    printf("Dinero inicial: ");
    scanf("%f", &dinero);

    // Abrir archivo en modo append (agregar al final)
    f = fopen("clientes.txt", "a");
    if(f == NULL) {
        printf("ERROR: No se pudo abrir clientes.txt\n");
        return;
    }

    // Guardamos datos en el archivo
    fprintf(f, "%s %s %.2f\n", user, pass, dinero);
    fclose(f);

    printf(" Usuario agregado correctamente.\n");
}

//funcion añadir producto

void añadirProducto() {
    FILE *f;
    char nombre[50];
    float precio;
    int stock;

    printf("\n--- Añadir Producto ---\n");
    printf("Nombre del producto: ");
    scanf("%49s", nombre);        // límite para evitar overflow
    printf("Precio: ");
    scanf("%f", &precio);
    printf("Stock (existencias): ");
    scanf("%d", &stock);

    f = fopen("productos.txt", "a");
    if(f == NULL) {
        printf("ERROR: No se pudo abrir productos.txt\n");
        return;
    }

    fprintf(f, "%s $%.2f existencias: %d\n", nombre, precio, stock);
    fclose(f);

    printf("Producto agregado correctamente.\n");
}

void eliminarUsuario() {
    FILE *f, *temp;
    char usuarioBuscado[30];
    char user[30], pass[30];
    float dinero;
    int encontrado = 0;

    printf("\n--- Eliminar Usuario ---\n");
    printf("Ingrese el usuario que desea eliminar: ");
    scanf("%s", usuarioBuscado);

    f = fopen("clientes.txt", "r");
    temp = fopen("temp.txt", "w");

    if(f == NULL || temp == NULL) {
        printf("ERROR: No se pudo abrir el archivo.\n");
        return;
    }

    while(fscanf(f, "%s %s %f", user, pass, &dinero) != EOF) {

        if(strcmp(user, usuarioBuscado) == 0) {
            encontrado = 1;
            continue;  // NO se copia → se elimina
        }

        // Copiar los que NO sean el usuario buscado
        fprintf(temp, "%s %s %.2f\n", user, pass, dinero);
    }

    fclose(f);
    fclose(temp);

    remove("clientes.txt");
    rename("temp.txt", "clientes.txt");

    if(encontrado)
        printf("\n✔ Usuario eliminado correctamente.\n");
    else
        printf("\n Usuario no encontrado.\n");
}

//modificar usuario
void modificarUsuario() {
    FILE *f, *temp;
    char usuarioBuscado[30];
    char user[30], pass[30];
    float dinero;
    int encontrado = 0;

    printf("\n--- Modificar Usuario ---\n");
    printf("Ingrese el usuario que desea modificar: ");
    scanf("%s", usuarioBuscado);

    f = fopen("clientes.txt", "r");
    temp = fopen("temp.txt", "w");

    if(f == NULL || temp == NULL) {
        printf("ERROR: No se pudo abrir el archivo.\n");
        return;
    }

    while(fscanf(f, "%s %s %f", user, pass, &dinero) != EOF) {

        if(strcmp(user, usuarioBuscado) == 0) {
            encontrado = 1;

            // Mostrar datos actuales
            printf("\n✔ Usuario encontrado.\n");
            printf("usuario: %s\n", user);
            printf("contraseña: %s\n", pass);
            printf("dinero: $%.2f\n\n", dinero);

            // Pedir nuevos valores
            printf("Ingrese los nuevos datos:\n");
            printf("Nuevo usuario: ");
            scanf("%s", user);

            printf("Nueva contraseña: ");
            scanf("%s", pass);

            printf("Nuevo dinero ($): ");
            scanf("%f", &dinero);
        }

        // Escribir registro actualizado o sin cambios
        fprintf(temp, "%s %s %.2f\n", user, pass, dinero);
    }

    fclose(f);
    fclose(temp);

    remove("clientes.txt");
    rename("temp.txt", "clientes.txt");

    if(encontrado)
        printf("\n✔ Usuario modificado correctamente.\n");
    else
        printf("\n Usuario no encontrado.\n");
}

//MODIFICAR PRODUCTOOOOO :)))

void modificarProducto() {
    FILE *f, *temp;
    char productoBuscado[50];
    char nombre[50];
    float precio;
    int stock;
    int encontrado = 0;

    printf("\n--- Modificar Producto ---\n");
    printf("Ingrese el nombre del producto que desea modificar: ");
    scanf("%s", productoBuscado);

    f = fopen("productos.txt", "r");
    temp = fopen("temp.txt", "w");

    if (f == NULL || temp == NULL) {
        printf("ERROR: No se pudo abrir el archivo.\n");
        return;
    }

    while (fscanf(f, "%s $%f existencias: %d", nombre, &precio, &stock) != EOF) {

        if (strcmp(nombre, productoBuscado) == 0) {
            encontrado = 1;

            // Mostrar datos actuales
            printf("\n✔ Producto encontrado.\n");
            printf("Nombre: %s\n", nombre);
            printf("Precio: $%.2f\n", precio);
            printf("Existencias: %d\n\n", stock);

            // Pedir nuevos valores
            printf("Ingrese los nuevos datos:\n");

            printf("Nuevo nombre: ");
            scanf("%s", nombre);

            printf("Nuevo precio ($): ");
            scanf("%f", &precio);

            printf("Nuevas existencias: ");
            scanf("%d", &stock);
        }

        // Escribir registro modificado o sin cambios
        fprintf(temp, "%s $%.2f existencias: %d\n", nombre, precio, stock);
    }

    fclose(f);
    fclose(temp);

    remove("productos.txt");
    rename("temp.txt", "productos.txt");

    if (encontrado)
        printf("\n✔ Producto modificado correctamente.\n");
    else
        printf("\n Producto no encontrado.\n");
}

// eliminar producto 

void eliminarProducto() {
    FILE *f, *temp;
    char productoBuscado[50];
    char nombre[50];
    float precio;
    int stock;
    int encontrado = 0;

    printf("\n--- Eliminar Producto ---\n");
    printf("Ingrese el nombre del producto que desea eliminar: ");
    scanf("%s", productoBuscado);

    f = fopen("productos.txt", "r");
    temp = fopen("temp.txt", "w");

    if (f == NULL || temp == NULL) {
        printf("ERROR: No se pudo abrir el archivo.\n");
        return;
    }

    while (fscanf(f, "%s $%f existencias: %d", nombre, &precio, &stock) != EOF) {

        if (strcmp(nombre, productoBuscado) == 0) {
            encontrado = 1;

            // Mostrar datos del producto antes de eliminarlo
            printf("\n✔ Producto encontrado.\n");
            printf("Nombre: %s\n", nombre);
            printf("Precio: $%.2f\n", precio);
            printf("Existencias: %d\n", stock);

            char confirmacion;
            printf("\n¿Seguro que quiere eliminar este producto? (s/n): ");
            scanf(" %c", &confirmacion);

            if (confirmacion == 's' || confirmacion == 'S') {
                // NO copiarlo → se elimina
                printf("\n✔ Producto eliminado correctamente.\n");
                continue;
            } else {
                // Si no se elimina, lo copiamos como estaba
                fprintf(temp, "%s $%.2f existencias: %d\n", nombre, precio, stock);
                printf("\n Eliminación cancelada por el usuario.\n");
                continue;
            }
        }

        // Copiar los que NO serán eliminados
        fprintf(temp, "%s $%.2f existencias: %d\n", nombre, precio, stock);
    }

    fclose(f);
    fclose(temp);

    remove("productos.txt");
    rename("temp.txt", "productos.txt");

    if (!encontrado)
        printf("\n Producto no encontrado.:(\n");
}

void modificarCostaProducto() {
    FILE *f, *temp;
    char productoBuscado[50];
    char nombre[50];
    float precio;
    int stock;
    int encontrado = 0;

    printf("\n--- Modificar Costo de Producto ---\n");
    printf("Ingrese el nombre del producto: ");
    scanf("%s", productoBuscado);

    f = fopen("productos.txt", "r");
    temp = fopen("temp.txt", "w");

    if (f == NULL || temp == NULL) {
        printf("ERROR al abrir archivo.\n");
        return;
    }

    while (fscanf(f, "%s $%f existencias: %d", nombre, &precio, &stock) != EOF) {

        if (strcmp(nombre, productoBuscado) == 0) {
            encontrado = 1;

            printf("\n✔ Producto encontrado.\n");
            printf("Costo actual: $%.2f\n", precio);

            printf("Nuevo costo: $");
            scanf("%f", &precio);
        }

        fprintf(temp, "%s $%.2f existencias: %d\n", nombre, precio, stock);
    }

    fclose(f);
    fclose(temp);

    remove("productos.txt");
    rename("temp.txt", "productos.txt");

    if (encontrado)
        printf("\n✔ Costo modificado correctamente.\n");
    else
        printf("\n Producto no encontrado.\n");
}





void modificarDineroUsuario() {
    FILE *f, *temp;
    char usuarioBuscado[30];
    char user[30], pass[30];
    float dinero;
    int encontrado = 0;

    printf("\n--- Modificar Dinero del Usuario ---\n");
    printf("Ingrese el nombre del usuario: ");
    scanf("%s", usuarioBuscado);

    f = fopen("clientes.txt", "r");
    temp = fopen("temp.txt", "w");

    if (f == NULL || temp == NULL) {
        printf("ERROR al abrir archivo.\n");
        return;
    }

    while (fscanf(f, "%s %s %f", user, pass, &dinero) != EOF) {

        if (strcmp(user, usuarioBuscado) == 0) {
            encontrado = 1;

            printf("\n✔ Usuario encontrado.\n");
            printf("Dinero actual: $%.2f\n", dinero);

            printf("Nuevo dinero: $");
            scanf("%f", &dinero);
        }

        fprintf(temp, "%s %s %.2f\n", user, pass, dinero);
    }

    fclose(f);
    fclose(temp);

    remove("clientes.txt");
    rename("temp.txt", "clientes.txt");

    if (encontrado)
        printf("\nDinero modificado correctamente. MIAU\n");
    else
        printf("\n Usuario no encontrado.\n");
}

//MARIOOOOO COMIENZA CON USUARIOOOO

void usuario() {
    char user[30], pass[30];
    char archivoUser[30], archivoPass[30];
    float dineroDisponible;
    int encontrado = 0;

    FILE *f;
    f = fopen("clientes.txt", "r");

    if (f == NULL) {
        printf("ERROR: No se pudo abrir clientes.txt\n");
        return;
    }

    printf("\n--- INICIO DE SESION CLIENTE ---\n");
    printf("Usuario: ");
    scanf("%s", user);
    printf("Contrasena: ");
    scanf("%s", pass);

    // Buscar usuario en archivo
    while (fscanf(f, "%s %s %f", archivoUser, archivoPass, &dineroDisponible) != EOF) {
        if (strcmp(user, archivoUser) == 0 && strcmp(pass, archivoPass) == 0) {
            encontrado = 1;
            break;
        }
    }

    fclose(f);

    if (!encontrado) {
        printf("\nUsuario o contrasena incorrectos.\nRegresando al menú principal...\n");
        return;
    }

    printf("\n✔ Bienvenido %s\n", user);
    printf("Saldo disponible: $%.2f\n\n", dineroDisponible);

    // SI ENTRA AQUI YA ESTÁ LOGEADO
    menuCliente(user, dineroDisponible);
}

// -----------------------------------------
//  MENU CLIENTEEEEEEEEEEEEEEEE
// -----------------------------------------
void menuCliente(char usuario[], float dineroDisponible) {
    int opc;
    float montoRecarga;

    do {
        printf("\n------ MENU CLIENTE ------\n");
        printf("1. Ver productos\n");
        printf("2. Comprar productos\n");
        printf("3. Recargar dinero\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opc);

        switch(opc) {
            case 1:
                mostrarProductos();
                break;
            case 2:
                comprarProducto(usuario, &dineroDisponible);
                break;
            case 3:
                printf("\nIngrese la cantidad a recargar: $");
                if (scanf("%f", &montoRecarga) != 1) {
                    printf("Entrada invalida.\n");
                    // limpiar buffer si hace falta
                    int c; while ((c = getchar()) != '\n' && c != EOF) ;
                    break;
                }
                if (montoRecarga <= 0) {
                    printf("Monto invalido.\n");
                    break;
                }
                dineroDisponible += montoRecarga;
                guardarDineroUsuario(usuario, dineroDisponible);
                printf("Recarga exitosa. Nuevo saldo: $%.2f\n", dineroDisponible);
                break;
            case 4:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }

    } while(opc != 4);
}



void mostrarProductos() {
    FILE *f;
    char nombre[50];
    float precio;
    int stock;

    f = fopen("productos.txt", "r");

    if (f == NULL) {
        printf("ERROR: No se pudo abrir productos.txt\n");
        return;
    }

    printf("\n--- PRODUCTOS DISPONIBLES ---\n");

    while (fscanf(f, "%s $%f existencias: %d", nombre, &precio, &stock) != EOF) {
        printf("Producto: %s | Precio: $%.2f | Stock: %d\n", nombre, precio, stock);
    }

    fclose(f);
}




//  GUARDAR DINERO USUARIO

void guardarDineroUsuario(char usuario[], float dineroNuevo) {
    FILE *f = fopen("clientes.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    char user[30], pass[30];
    float dinero;
    int encontrado = 0;

    if (!f || !temp) {
        printf("Error al abrir archivos para actualizar saldo.\n");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }

    while (fscanf(f, "%29s %29s %f", user, pass, &dinero) == 3) {
        if (strcmp(user, usuario) == 0) {
            dinero = dineroNuevo;
            encontrado = 1;
        }
        fprintf(temp, "%s %s %.2f\n", user, pass, dinero);
    }

    fclose(f);
    fclose(temp);

    remove("clientes.txt");
    rename("temp.txt", "clientes.txt");

    if (!encontrado) {
        printf("Aviso: usuario %s no encontrado al guardar dinero (no se actualizó archivo).\n", usuario);
    }
}


// -----------------------------------------
//  COMPRARRR PRODUCTOOO
// -----------------------------------------
void comprarProducto(char usuario[], float *dineroDisponible) {
    char producto[50], nombre[50];
    float precio;
    int stock, cantidad;
    int encontrado = 0;
    FILE *f = NULL, *temp = NULL;

    mostrarProductos();

    printf("\nIngrese el nombre del producto que desea comprar: ");
    scanf("%49s", producto);

    f = fopen("productos.txt", "r");
    if (!f) {
        printf("Error: no se pudo abrir productos.txt\n");
        return;
    }
    temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Error: no se pudo crear archivo temporal.\n");
        fclose(f);
        return;
    }

    while (fscanf(f, "%49s $%f existencias: %d", nombre, &precio, &stock) == 3) {
        if (strcmp(nombre, producto) == 0) {
            encontrado = 1;
            printf("Cuantos desea comprar? ");
            if (scanf("%d", &cantidad) != 1) {
                printf("Cantidad invalida.\n");
                // copiar registro tal cual y seguir
                fprintf(temp, "%s $%.2f existencias: %d\n", nombre, precio, stock);
                int c; while ((c = getchar()) != '\n' && c != EOF) ;
                continue;
            }

            if (cantidad > stock) {
                printf("\nNo hay suficientes existencias.\n");
                // No cambio stock, lo escribimos igual
                fprintf(temp, "%s $%.2f existencias: %d\n", nombre, precio, stock);
                continue;
            }

            float total = precio * cantidad;
            // aplicar cupon si el usuario tiene uno
            total = usarCupon(total);

            if (total > *dineroDisponible) {
                printf("\nNo tiene suficiente dinero.\n");
                printf("Faltan: $%.2f\n", total - *dineroDisponible);
                // escribimos el registro sin modificar
                fprintf(temp, "%s $%.2f existencias: %d\n", nombre, precio, stock);
                continue;
            }

            // compra exitosa: actualizar dinero y stock
            *dineroDisponible -= total;
            stock -= cantidad;

            printf("\n Compra realizada con exito.\n");
            generarTicket(usuario, producto, cantidad, precio, total);

            // persistir nuevo saldo del usuario en archivo clientes
            guardarDineroUsuario(usuario, *dineroDisponible);
        }

        // escribir registro (modificado si era el comprado, o idéntico si no)
        fprintf(temp, "%s $%.2f existencias: %d\n", nombre, precio, stock);
    }

    fclose(f);
    fclose(temp);

    remove("productos.txt");
    rename("temp.txt", "productos.txt");

    if (!encontrado) {
        printf("\nProducto no encontrado.\n");
    }
}


void generarTicket(char usuario[], char producto[], int cantidad, float precioUnitario, float total) {
    FILE *t;
    time_t ahora;
    time(&ahora);

    t = fopen("ticket.txt", "a"); // Se agrega al final para guardar muchos tickets

    if (t == NULL) {
        printf("ERROR: No se pudo crear ticket.txt\n");
        return;
    }

    fprintf(t, "=====================================\n");
    fprintf(t, "          TICKET DE COMPRA\n");
    fprintf(t, "=====================================\n");
    fprintf(t, "Cliente: %s\n", usuario);
    fprintf(t, "Fecha: %s", ctime(&ahora)); // Fecha y hora automática
    fprintf(t, "-------------------------------------\n");
    fprintf(t, "Producto: %s\n", producto);
    fprintf(t, "Cantidad: %d\n", cantidad);
    fprintf(t, "Precio unitario: $%.2f\n", precioUnitario);
    fprintf(t, "Total pagado: $%.2f\n", total);
    fprintf(t, "-------------------------------------\n");
    fprintf(t, " ¡Gracias por su compra! WOF WOF\n");
    fprintf(t, "=====================================\n\n");

    fclose(t);

    printf("\n Ticket generado correctamente (ticket.txt)\n");
}


void agregarCupon() {
    FILE *f = fopen("cupones.txt", "a");
    if (!f) {
        printf("Error al abrir cupones.txt\n");
        return;
    }

    char codigo[50];
    int descuento;

    printf("Ingrese el codigo del cupon: ");
    scanf("%s", codigo);

    printf("Ingrese el porcentaje de descuento (1-100): ");
    scanf("%d", &descuento);

    if (descuento < 1 || descuento > 100) {
        printf("Descuento invalido.\n");
        return;
    }

    fprintf(f, "%s %d\n", codigo, descuento);
    fclose(f);

    printf("\nCupon agregado correctamente!\n");
}


float usarCupon(float total) {
    FILE *f = fopen("cupones.txt", "r");
    if (!f) {
        printf("No hay cupones disponibles.\n");
        return total;
    }

    char codigo[50], codigoIngresado[50];
    int descuento;

    printf("¿Tiene algún cupón? (s/n): ");
    char op;
    scanf(" %c", &op);

    if (op == 'n' || op == 'N') {
        fclose(f);
        return total;
    }

    printf("Ingrese el código del cupón: ");
    scanf("%s", codigoIngresado);

    while (fscanf(f, "%s %d", codigo, &descuento) == 2) {
        if (strcmp(codigo, codigoIngresado) == 0) {
            fclose(f);

            float rebaja = total * (descuento / 100.0);
            float totalFinal = total - rebaja;

            printf("\n✔ Cupón válido (%d%% de descuento)\n", descuento);
            printf("Descuento aplicado: -$%.2f\n", rebaja);
            printf("Nuevo total: $%.2f\n", totalFinal);

            return totalFinal;
        }
    }

    fclose(f);
    printf("\n Cupón no encontrado o inválido.\n");
    return total; // No aplica descuento
}
















