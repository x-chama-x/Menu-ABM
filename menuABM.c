#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

enum tipoUsuario {ALUMNO, PROFESOR};
enum estadoUsuario {ACTIVO, INACTIVO};
// Definición de una estructura para almacenar los datos de usuario
struct Usuario {
    int id_usuario;
    enum tipoUsuario tipo;
    char nombre[45];
    char apellido[45];
    char email[255];
    char contrasena[32];
    enum estadoUsuario estado;
};

// Definición de una estructura para almacenar los datos de materia
struct Materia {
    int id_materia;
    char nombre[45];
};

// Definición de una estructura para almacenar los datos de curso
struct Curso {
    int id_cursada;
    char anio_division[45];
};

// Definición de una estructura para almacenar las calificaciones
struct Calificacion {
    int id_calificacion;
    int id_alumno;
    int id_materia;
    int nota;
    int num_examen;
};

// Prototipos de funciones
void menuPrincipal();
void submenuAlumno(FILE *);
void submenuProfesor(FILE *);
void submenuConsulta();
void TeclaParaContinuar();
const char* getTipoUsuario(enum tipoUsuario);
const char* getEstadoUsuario(enum estadoUsuario);
void altaAlumno(FILE *);
void altaProfesor(FILE *);
void altaMateria(FILE *);
void altaCurso(FILE *);
void altaCalificacion(FILE *);
void bajaAlumno(FILE *);
void bajaProfesor(FILE *);
void modificarAlumno(FILE *);
void modificarProfesor(FILE *);
void consultarUsuarios();
void consultarAlumnos();

int main() {
    menuPrincipal(); // Llama a la función del menú principal
    return 0;
}

// funciones para las operaciones de alta
void altaAlumno(FILE *fAlumnos){
    struct Usuario nuevoAlumno;
    printf("Ingrese el id del alumno: ");
    scanf("%d", &nuevoAlumno.id_usuario);
    nuevoAlumno.tipo = ALUMNO;
    printf("Ingrese el nombre del alumno: ");
    scanf("%s", nuevoAlumno.nombre);
    printf("Ingrese el apellido del alumno: ");
    scanf("%s", nuevoAlumno.apellido);
    printf("Ingrese el email del alumno: ");
    scanf("%s", nuevoAlumno.email);
    printf("Ingrese la contrase%ca del alumno: ", 164);
    scanf("%s", nuevoAlumno.contrasena);
    nuevoAlumno.estado = ACTIVO;
    fseek(fAlumnos, 0L, SEEK_END);
    fwrite(&nuevoAlumno, sizeof(struct Usuario), 1, fAlumnos);
}
void altaProfesor(FILE *fProfesores){
    struct Usuario nuevoProfesor;
    printf("Ingrese el id del profesor: ");
    scanf("%d", &nuevoProfesor.id_usuario);
    nuevoProfesor.tipo = PROFESOR;
    printf("Ingrese el nombre del profesor: ");
    scanf("%s", nuevoProfesor.nombre);
    printf("Ingrese el apellido del profesor: ");
    scanf("%s", nuevoProfesor.apellido);
    printf("Ingrese el email del profesor: ");
    scanf("%s", nuevoProfesor.email);
    printf("Ingrese la contrase%ca del profesor: ", 164);
    scanf("%s", nuevoProfesor.contrasena);
    nuevoProfesor.estado = ACTIVO;
    fseek(fProfesores, 0L, SEEK_END);
    fwrite(&nuevoProfesor, sizeof(struct Usuario), 1, fProfesores);
}

void altaCurso(FILE *fCursos){
    struct Curso nuevoCurso;
    printf("Ingrese el id del curso: ");
    scanf("%d", &nuevoCurso.id_cursada);
    printf("Ingrese el a%co y divisi%cn del curso: ", 164, 162);
    scanf("%s", nuevoCurso.anio_division);
    fseek(fCursos, 0L, SEEK_END);
    fwrite(&nuevoCurso, sizeof(struct Curso), 1, fCursos);
}


void altaMateria(FILE *fMaterias){
    struct Materia nuevaMateria;
    printf("Ingrese el id de la materia: ");
    scanf("%d", &nuevaMateria.id_materia);
    printf("Ingrese el nombre de la materia: ");
    scanf("%s", nuevaMateria.nombre);
    fseek(fMaterias, 0L, SEEK_END);
    fwrite(&nuevaMateria, sizeof(struct Materia), 1, fMaterias);
}

void altaCalificacion(FILE *fCalificaciones){
    struct Calificacion nuevaCalificacion;
    printf("Ingrese el id de la calificaci%cn: ", 162);
    scanf("%d", &nuevaCalificacion.id_calificacion);
    printf("Ingrese el id del alumno: ");
    scanf("%d", &nuevaCalificacion.id_alumno);
    printf("Ingrese el id de la materia: ");
    scanf("%d", &nuevaCalificacion.id_materia);
    printf("Ingrese la nota: ");
    scanf("%d", &nuevaCalificacion.nota);
    printf("Ingrese el n%cmero de examen: ", 163);
    scanf("%d", &nuevaCalificacion.num_examen);
    fseek(fCalificaciones, 0L, SEEK_END);
    fwrite(&nuevaCalificacion, sizeof(struct Calificacion), 1, fCalificaciones);
}

// funciones para las operaciones de baja
void bajaAlumno(FILE *fAlumnos) {
    struct Usuario alumno;
    int id;
    printf("Ingrese el ID del alumno a dar de baja: ");
    scanf("%d", &id);
    int encontrado = 0; // flag que indica si se encontró el alumno
    rewind(fAlumnos);
    fread(&alumno, sizeof(struct Usuario), 1, fAlumnos);
    while (!feof(fAlumnos) && !encontrado) {
        if (alumno.tipo == ALUMNO && alumno.id_usuario == id) {
            encontrado = 1;
            alumno.estado = INACTIVO;
            fseek(fAlumnos, -sizeof(struct Usuario), SEEK_CUR);
            fwrite(&alumno, sizeof(struct Usuario), 1, fAlumnos);
        } else {
            fread(&alumno, sizeof(struct Usuario), 1, fAlumnos);
        }
    }

    if (encontrado) {
        printf("El alumno con ID %d ha sido dado de baja.\n", id);
        TeclaParaContinuar();
    } else {
        printf("No se encontro ningun alumno con ID %d.\n", id);
        TeclaParaContinuar();
    }
}


void bajaProfesor(FILE *fProfesores){
    struct Usuario bajaProfesor;
    printf("Ingrese el id del profesor a dar de baja: ");
    scanf("%d", &bajaProfesor.id_usuario);
}

// funciones para las operaciones de modificación
void modificarAlumno(FILE *fAlumnos){
    struct Usuario modificarAlumno;
    printf("Ingrese el id del alumno a modificar: ");
    scanf("%d", &modificarAlumno.id_usuario);
    printf("Ingrese el nombre del alumno a modificar: ");
    scanf("%s", modificarAlumno.nombre);
    printf("Ingrese el apellido del alumno a modificar: ");
    scanf("%s", modificarAlumno.apellido);
    printf("Ingrese el email del alumno a modificar: ");
    scanf("%s", modificarAlumno.email);
    printf("Ingrese la contraseña del alumno a modificar: ");
    scanf("%s", modificarAlumno.contrasena);
    printf("Ingrese el estado del alumno a modificar (activo/inactivo): ");
    scanf("%s", modificarAlumno.estado);
}

void modificarProfesor(FILE *fProfesores){
    struct Usuario modificarProfesor;
    printf("Ingrese el id del profesor a modificar: ");
    scanf("%d", &modificarProfesor.id_usuario);
    printf("Ingrese el nombre del profesor a modificar: ");
    scanf("%s", modificarProfesor.nombre);
    printf("Ingrese el apellido del profesor a modificar: ");
    scanf("%s", modificarProfesor.apellido);
    printf("Ingrese el email del profesor a modificar: ");
    scanf("%s", modificarProfesor.email);
    printf("Ingrese la contraseña del profesor a modificar: ");
    scanf("%s", modificarProfesor.contrasena);
    printf("Ingrese el estado del profesor a modificar (activo/inactivo): ");
    scanf("%s", modificarProfesor.estado);
}

// Función para mostrar el menú principal
void menuPrincipal() {
    int opcion;
    FILE *fAlumnos, *fProfesores, *fMaterias, *fCursos, *fCalificaciones;
    if ((fAlumnos = fopen("alumnos.dat", "rb+")) == NULL)
    {
        fAlumnos = fopen("alumnos.dat", "wb+");
    }
    if ((fProfesores = fopen("profesores.dat", "rb+")) == NULL)
    {
        fProfesores = fopen("profesores.dat", "wb+");
    }
    if ((fMaterias = fopen("materias.dat", "rb+")) == NULL)
    {
        fMaterias = fopen("materias.dat", "wb+");
    }
    if ((fCursos = fopen("cursos.dat", "rb+")) == NULL)
    {
        fCursos = fopen("cursos.dat", "wb+");
    }
    if ((fCalificaciones = fopen("calificaciones.dat", "rb+")) == NULL)
    {
        fCalificaciones = fopen("calificaciones.dat", "wb+");
    }
    do {
        system("cls"); // Limpiar la pantalla
        printf("----- Men%c Principal -----\n", 163);
        printf("1. Alumno\n");
        printf("2. Profesor\n");
        printf("3. Materia\n");
        printf("4. Curso\n");
        printf("5. Calificaci%cn\n", 162);
        printf("6. Consulta\n");
        printf("7. Salir\n");
        printf("Selecciona una opci%cn: ", 162);
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                // Submenú de alumno
                submenuAlumno(fAlumnos);
                break;
            case 2:
                // Submenú de profesor
                submenuProfesor(fProfesores);
                break;
            case 3:
                // Agregar una materia
                altaMateria(fMaterias);
                break;
            case 4:
                // Agregar un curso
                altaCurso(fCursos);
                break;
            case 5:
                // Agregar una calificación
                altaCalificacion(fCalificaciones);
                break;
            case 6:
                // Submenú de consulta
                submenuConsulta();
                break;
            case 7:
                printf("Saliendo del programa. %cHasta luego!\n", 173);
                break;
            default:
                printf("Opci%cn no v%clida.\n", 162, 160);
                TeclaParaContinuar();
                break;
        }
    } while (opcion != 7);
    fclose(fAlumnos);
    fclose(fProfesores);
    fclose(fMaterias);
    fclose(fCursos);
    fclose(fCalificaciones);
}

void submenuAlumno(FILE *fAlumnos) {
    int aluOpcion;
    do {
        system("cls"); // Limpiar la pantalla
        printf("\n----- Men%c de Alumno -----\n", 163);
        printf("1. Alta\n");
        printf("2. Baja\n");
        printf("3. Modificaci%cn\n", 162);
        printf("4. Consulta\n");
        printf("5. Volver al Men%c Principal\n", 163);
        printf("Selecciona una opci%cn: ", 162);
        scanf("%d", &aluOpcion);

        switch (aluOpcion) {
            case 1:
                altaAlumno(fAlumnos);
                break;
            case 2:
                bajaAlumno(fAlumnos);
                break;
            case 3:
                modificarAlumno(fAlumnos);
                break;
            case 4:
                consultarAlumnos(fAlumnos);
                break;
            case 5:
                break;
            default:
                printf("Opci%cn no v%clida.\n", 162, 160);
                TeclaParaContinuar();
                break;
        }
    } while (aluOpcion != 5);
}

void submenuProfesor(FILE *fProfesores) {
    int profOpcion;
    do {
        system("cls"); // Limpiar la pantalla
        printf("\n----- Men%c de Profesor -----\n", 163);
        printf("1. Alta\n");
        printf("2. Baja\n");
        printf("3. Modificaci%cn\n", 162);
        printf("4. Consulta\n");
        printf("5. Volver al Men%c Principal\n", 163);
        printf("Selecciona una opci%cn: ", 162);
        scanf("%d", &profOpcion);

        switch (profOpcion) {
            case 1:
                altaProfesor(fProfesores);
                break;
            case 2:
                bajaProfesor(fProfesores);
                break;
            case 3:
                modificarProfesor(fProfesores);
                break;
            case 4:
                // consulta profesores
                break;
            case 5:
                // Volver al menú principal
                break;
            default:
                printf("Opci%cn no v%clida.\n", 162, 160);
                TeclaParaContinuar();
                break;
        }
    } while (profOpcion != 5);
}

void submenuConsulta() {
    int altaOpcion;
    do {
        system("cls"); // Limpiar la pantalla
        printf("\n----- Men%c de Consulta -----\n", 163);
        printf("1. Consultar Usuarios\n");
        printf("2. Consultar Cursos y Materias\n");
        printf("3. Consultar Calificaciones\n");
        printf("4. Volver al Men%c Principal\n", 163);
        printf("Selecciona una opci%cn: ", 162);
        scanf("%d", &altaOpcion);

        switch (altaOpcion) {
            case 1:
                //consultarUsuarios();
                break;
            case 2:
                //consultarCursosMaterias();
                break;
            case 3:
                //consultarCalificaciones();
                break;
            case 4:
                // Volver al menú principal
                break;
            default:
                printf("Opci%cn no v%clida.\n", 162, 160);
                TeclaParaContinuar();
                break;
        }
    } while (altaOpcion != 4);
}

void TeclaParaContinuar() {
    printf("\nPresiona una tecla para continuar...");
    getch();
}

const char* getTipoUsuario(enum tipoUsuario tipo) {
    switch (tipo) {
        case ALUMNO:
            return "Alumno";
        case PROFESOR:
            return "Profesor";
        default:
            return "Desconocido";
    }
}

const char* getEstadoUsuario(enum estadoUsuario estado) {
    switch (estado) {
        case ACTIVO:
            return "Activo";
        case INACTIVO:
            return "Inactivo";
        default:
            return "Desconocido";
    }
}

void consultarAlumnos(FILE *fAlumnos){
    struct Usuario alumno;
    rewind(fAlumnos);
    int hayAlumnos = 0;
    while (fread(&alumno, sizeof(struct Usuario), 1, fAlumnos) == 1){
        if (alumno.tipo == ALUMNO){
            printf("\nId: %d\n", alumno.id_usuario);
            printf("Nombre: %s\n", alumno.nombre);
            printf("Apellido: %s\n", alumno.apellido);
            printf("Email: %s\n", alumno.email);
            printf("Contrase%ca: %s\n", 164, alumno.contrasena);
            printf("Estado: %s\n", getEstadoUsuario(alumno.estado));
            hayAlumnos = 1;
        } 
    }
    if (!hayAlumnos){
        printf("\nNo hay alumnos cargados.\n");
    }
    TeclaParaContinuar();
}

