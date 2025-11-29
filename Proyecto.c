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
        printf("\n----- MENU ADMIN  -----\n");
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
//borrar usuario

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
                printf("\n❗ Eliminación cancelada por el usuario.\n");
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
    getchar(); // Limpia buffer
    char nombreBusca[50];
    printf("\n--- Modificar Costo de Producto ---\n");
    printf("Ingresa el nombre del producto: ");
    fgets(nombreBusca, sizeof(nombreBusca), stdin);
    nombreBusca[strcspn(nombreBusca, "\n")] = 0;

    int encontrado = -1;

    for (int i = 0; i < totalProductos; i++) {
        if (strcmp(productos[i].nombre, nombreBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf(" Producto no encontrado.\n");
        return;
    }

    float nuevoCosto;
    printf("Costo actual: $ %.2f\n", productos[encontrado].costo);
    printf("Nuevo costo: $ ");
    scanf("%f", &nuevoCosto);

    productos[encontrado].costo = nuevoCosto;

    printf(" Costo actualizado correctamente.\n");
}



void modificarDineroUsuario() {
    getchar(); // Limpiar buffer
    char nombreBusca[50];
    printf("\n--- Modificar Dinero del Usuario ---\n");
    printf("Ingrese el nombre del usuario: ");
    fgets(nombreBusca, sizeof(nombreBusca), stdin);
    nombreBusca[strcspn(nombreBusca, "\n")] = 0;

    int encontrado = -1;

    // Buscar usuario
    for (int i = 0; i < totalUsuarios; i++) {
        if (strcmp(usuarios[i].nombre, nombreBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("❌ Usuario no encontrado.\n");
        return;
    }

    // Mostrar información actual
    printf("\n--- Datos actuales ---\n");
    printf("Nombre: %s\n", usuarios[encontrado].nombre);
    printf("Contraseña: %s\n", usuarios[encontrado].password);
    printf("Dinero actual: $ %.2f\n", usuarios[encontrado].dinero);

    // Pedir nuevo dinero
    float nuevoDinero;
    printf("\nIngrese el nuevo dinero del usuario: $ ");
    scanf("%f", &nuevoDinero);

    usuarios[encontrado].dinero = nuevoDinero;

    printf("✔ Dinero actualizado correctamente.\n");
}







