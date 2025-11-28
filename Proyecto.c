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
void usuario();
int comprarProducto();
int recargarDinero();
int totalCompra();
int agregarProducto();
//Variables globales
int opcion;
//variables struct
//MENU PRINCIPAL
int main(){
    do{
    printf("******* WHISKERPETS *******\n");
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
        printf("\n----- MENU ADMINISTRADOR -----\n");
        printf("1. Añadir Usuario\n");
        printf("2. Modificar Usuario\n");
        printf("3. Eliminar Usuario\n");
        printf("4. Añadir Producto\n");
        printf("5. Modificar Producto\n");
        printf("6. Eliminar Producto\n");
        printf("7. Modificar Dinero de Usuario\n");
        printf("8. Modificar Costo de Producto\n");
        printf("9. Salir\n");
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
            case 9: printf("Saliendo del administrador...\n"); break;
            default: printf("Opción no valida.\n");
        }

    } while(opc != 9);
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
    scanf("%s", nombre);
    printf("Precio: ");
    scanf("%f", &precio);
    printf("Stock (existencias): ");
    scanf("%d", &stock);

    f = fopen("productos.txt", "a");
    if(f == NULL) {
        printf("ERROR: No se pudo abrir productos.txt\n");
        return;
    }

    // Guardamos con formato amigable
    fprintf(f, "%s $%.2f existencias: %d\n", nombre, precio, stock);
    fclose(f);

    printf("Producto agregado correctamente.\n");
}




