//#include "../include/stylus_sdk.h"
//#include "../stylus-sdk-c/include/stylus_utils.h"
//#include "../stylus-sdk-c/include/storage.h"
//#include "../stylus-sdk-c/include/string.h"

///**
// * Este contrato es un challenge de 4 preguntas.
// * - Solo el owner puede activar/desactivar el challenge y cambiar las preguntas.
// * - Los participantes deben responder las 4 preguntas en orden.
// * - Las primeras 5 personas en completarlo (responder correctamente las 4) serán marcadas como ganadoras.
// */

//// Configuraciones
//#define MAX_WINNERS 5
//#define MAX_STUDENTS 200
//#define MAX_QUESTION_LEN 64
//#define MAX_ANSWER_LEN 64


//// Estructuras
//typedef struct {
//    uint8_t address[32];        // Dirección del estudiante (32 bytes)
//    uint8_t current_question;   // Pregunta actual que el estudiante debe responder (0-3)
//} Student;

//typedef struct {
//    uint8_t owner[32];                // Owner del contrato
//    bool active;                      // Si el reto está activo
//    uint16_t winner_count;            // Cantidad de ganadores actuales
//    uint8_t winners[MAX_WINNERS][32]; // Lista de ganadores (hasta 5)

//    // Almacenamiento de estudiantes
//    Student students[MAX_STUDENTS];

//    // Preguntas y respuestas correctas
//    char questions[4][MAX_QUESTION_LEN];
//    char answers[4][MAX_ANSWER_LEN];
//} Contract;

//Contract contract;

//static int	ft_memcmp(void *dest, void *src, size_t n)
//{
//	unsigned char	*ptr1;
//	unsigned char	*ptr2;

//	ptr1 = (unsigned char *)dest;
//	ptr2 = (unsigned char *)src;
//	while (n--)
//	{
//		if (*ptr1 != *ptr2)
//			return (*ptr1 - *ptr2);
//		ptr1++;
//		ptr2++;
//	}
//	return (0);
//}

//static void	ft_bzero(void *s, size_t n)
//{
//	unsigned char	*ptr;

//	ptr = (unsigned char *)s;
//	while (n--)
//		*ptr++ = 0;
//}

//static void	ft_memcpy(void *dest, void *src, size_t n)
//{
//	unsigned char	*ptr1;
//	unsigned char	*ptr2;

//	ptr1 = (unsigned char *)dest;
//	ptr2 = (unsigned char *)src;
//	while (n--)
//		*ptr1++ = *ptr2++;
//}

//static void	ft_strlcpy(char *dst, const char *src, size_t size)
//{
//	size_t	i;

//	i = 0;
//	while (i < size - 1 && src[i])
//	{
//		dst[i] = src[i];
//		i++;
//	}
//	dst[i] = 0;
//}

//static size_t	ft_strlen(const char *str)
//{
//	size_t	len;

//	len = 0;
//	while (str[len])
//		len++;
//	return (len);
//}

//static int	ft_strcmp(const char *s1, const char *s2)
//{
//	while (*s1 && *s1 == *s2)
//	{
//		s1++;
//		s2++;
//	}
//	return (*(unsigned char *)s1 - *(unsigned char *)s2);
//}


//// Funciones auxiliares
//static Student* find_or_create_student(uint8_t *student_address) {
//    for (int i = 0; i < MAX_STUDENTS; i++) {
//        if (ft_memcmp(contract.students[i].address, student_address, 32) == 0) {
//            return &contract.students[i];
//        }
//    }

//    // Si no existe, crear nuevo registro
//    for (int i = 0; i < MAX_STUDENTS; i++) {
//        // Buscamos un slot libre (direccion vacía)
//        uint8_t empty[32];
//        ft_bzero(empty, 32);
//        if (ft_memcmp(contract.students[i].address, empty, 32) == 0) {
//            ft_memcpy(contract.students[i].address, student_address, 32);
//            contract.students[i].current_question = 0;
//            return &contract.students[i];
//        }
//    }
//    return NULL; // Sin espacio
//}

//static bool is_owner(uint8_t *sender) {
//    return (ft_memcmp(contract.owner, sender, 32) == 0);
//}

//static ArbResult _return_bool(bool val) {
//    uint8_t ret = val ? 1 : 0;
//    ArbResult res = {Success, &ret, 1};
//    return res;
//}

//static ArbResult _return_uint8(uint8_t val) {
//    uint8_t ret = val;
//    ArbResult res = {Success, &ret, 1};
//    return res;
//}

//static ArbResult _return_winners() {
//    // Retornamos las direcciones de los ganadores concatenadas
//    // Cada ganador son 32 bytes, hasta MAX_WINNERS
//    size_t total_len = contract.winner_count * 32;
//    uint8_t output[total_len];
//    ft_bzero(output, total_len);

//    for (int i = 0; i < contract.winner_count; i++) {
//        ft_memcpy(output + (i * 32), contract.winners[i], 32);
//    }

//    ArbResult res = {Success, output, total_len};
//    return res;
//}

//// Funciones del contrato

//// init(owner)
//ArbResult init(uint8_t *sender, uint8_t *input, size_t len) {
//    // Inicializa el contrato, guardando al owner
//    ft_memcpy(contract.owner, sender, 32);
//    contract.active = false;
//    contract.winner_count = 0;

//    // Preguntas y respuestas por defecto (pueden ser cambiadas luego por el owner)
//    ft_strlcpy(contract.questions[0], "Who are you?", MAX_QUESTION_LEN);
//    ft_strlcpy(contract.answers[0], "The one who knocks", MAX_ANSWER_LEN);

//    ft_strlcpy(contract.questions[1], "who creates Bitcoin?", MAX_QUESTION_LEN);
//    ft_strlcpy(contract.answers[1], "Satoshi Nakamoto", MAX_ANSWER_LEN);

//    ft_strlcpy(contract.questions[2], "What is the meaning of bit?", MAX_QUESTION_LEN);
//    ft_strlcpy(contract.answers[2], "Binary digit", MAX_ANSWER_LEN);

//    ft_strlcpy(contract.questions[3], "Which is the beast way to learn code?", MAX_QUESTION_LEN);
//    ft_strlcpy(contract.answers[3], "Coding", MAX_ANSWER_LEN);

//    return _return_short_string(Success, "Contract initialized");
//}

//// set_active(bool) - Solo owner
//ArbResult set_active(uint8_t *sender, uint8_t *input, size_t len) {
//    if (!is_owner(sender)) {
//        return _return_short_string(Failure, "Only owner");
//    }
//    if (len < 1) {
//        return _return_short_string(Failure, "Missing bool");
//    }

//    bool val = (input[0] != 0);
//    contract.active = val;
//    return _return_short_string(Success, val ? "Activated" : "Deactivated");
//}

//// set_questions(q1, a1, q2, a2, q3, a3, q4, a4) - Solo owner
//// input vendrá codificado como:
////  q1\0a1\0q2\0a2\0q3\0a3\0q4\0a4\0
//ArbResult set_questions(uint8_t *sender, uint8_t *input, size_t len) {
//    if (!is_owner(sender)) {
//        return _return_short_string(Failure, "Only owner");
//    }

//    // Separar las strings por \0
//    // Esperamos 8 strings consecutivas.
//    char *parts[8];
//    char *ptr = (char*)input;
//    int count = 0;
//    for (int i = 0; i < 8; i++) {
//        if ((size_t)(ptr - (char*)input) >= len) {
//            return _return_short_string(Failure, "Invalid input");
//        }
//        parts[i] = ptr;
//        size_t slen = ft_strlen(ptr);
//        ptr += (slen + 1);
//        count++;
//    }

//    if (count < 8) {
//        return _return_short_string(Failure, "Not enough input");
//    }

//    // Copiamos a nuestras variables
//    for (int i = 0; i < 4; i++) {
//        ft_strlcpy(contract.questions[i], parts[i*2], MAX_QUESTION_LEN);
//        ft_strlcpy(contract.answers[i], parts[i*2+1], MAX_ANSWER_LEN);
//    }

//    return _return_short_string(Success, "Questions set");
//}

//// is_active() view
//ArbResult is_active(uint8_t *input, size_t len) {
//    return _return_bool(contract.active);
//}

//// get_current_question(address student)
//ArbResult get_current_question(uint8_t *input, size_t len) {
//    if (len < 32) {
//        return _return_short_string(Failure, "Missing address");
//    }

//    uint8_t student_address[32];
//    ft_memcpy(student_address, input, 32);

//    Student* student = find_or_create_student(student_address);
//    if (!student) {
//        return _return_short_string(Failure, "No student slot");
//    }

//    return _return_uint8(student->current_question);
//}

//// get_question_text(uint8_t q_id)
//ArbResult get_question_text(uint8_t *input, size_t len) {
//    if (len < 1) {
//        return _return_short_string(Failure, "No question id");
//    }
//    uint8_t q_id = input[0];
//    if (q_id > 3) {
//        return _return_short_string(Failure, "Invalid question id");
//    }

//    size_t slen = ft_strlen(contract.questions[q_id]);
//    ArbResult res = {Success, (uint8_t*)contract.questions[q_id], slen};
//    return res;
//}

//// verify_answer(address, answer)
//// input = student_address(32 bytes) + answer(null-terminated string)
//ArbResult verify_answer(uint8_t *sender, uint8_t *input, size_t len) {
//    if (!contract.active) {
//        return _return_short_string(Failure, "Contract not active");
//    }

//    if (contract.winner_count >= MAX_WINNERS) {
//        return _return_short_string(Failure, "Max winners reached");
//    }

//    if (len < 33) {
//        return _return_short_string(Failure, "Invalid input");
//    }

//    uint8_t student_address[32];
//    ft_memcpy(student_address, input, 32);
//    char *answer = (char *)(input + 32);

//    Student *student = find_or_create_student(student_address);
//    if (!student) {
//        return _return_short_string(Failure, "No student slot");
//    }

//    if (student->current_question >= 4) {
//        return _return_short_string(Failure, "Already completed");
//    }

//    uint8_t q_id = student->current_question;
//    if (ft_strcmp(answer, contract.answers[q_id]) == 0) {
//        // Respuesta correcta, avanzar
//        student->current_question++;
//        if (student->current_question == 4) {
//            // Completó las 4 preguntas
//            ft_memcpy(contract.winners[contract.winner_count], student_address, 32);
//            contract.winner_count++;
//            return _return_short_string(Success, "Winner!");
//        } else {
//            return _return_short_string(Success, "Correct! Next question");
//        }
//    } else {
//        return _return_short_string(Failure, "Wrong answer");
//    }
//}

//// get_winners()
//ArbResult get_winners_fn(uint8_t *input, size_t len) {
//    return _return_winners();
//}

//// is_winner(address)
//ArbResult is_winner_fn(uint8_t *input, size_t len) {
//    if (len < 32) {
//        return _return_short_string(Failure, "Invalid input");
//    }

//    uint8_t addr[32];
//    ft_memcpy(addr, input, 32);

//    for (int i = 0; i < contract.winner_count; i++) {
//        if (ft_memcmp(contract.winners[i], addr, 32) == 0) {
//            return _return_bool(true);
//        }
//    }
//    return _return_bool(false);
//}

//// get_owner()
//ArbResult get_owner(uint8_t *input, size_t len) {
//    ArbResult res = {Success, contract.owner, 32};
//    return res;
//}

//int handler(size_t argc) {
//    // Leer calldata
//    uint8_t argv[argc];
//    read_args(argv);

//    // Definir las funciones disponibles
//    FunctionRegistry registry[] = {
//        {to_function_selector("init()"), init},
//        {to_function_selector("set_active(bool)"), set_active},
//        {to_function_selector("set_questions(string)"), set_questions}, // Se espera input formateado
//        {to_function_selector("is_active()"), is_active},
//        {to_function_selector("get_current_question(address)"), get_current_question},
//        {to_function_selector("get_question_text(uint8)"), get_question_text},
//        {to_function_selector("verify_answer(bytes)"), verify_answer},
//        {to_function_selector("get_winners()"), get_winners_fn},
//        {to_function_selector("is_winner(address)"), is_winner_fn},
//        {to_function_selector("get_owner()"), get_owner},
//    };

//    uint32_t signature = *((uint32_t *)argv);

//    ArbResult res = call_function(registry, sizeof(registry)/sizeof(registry[0]), signature, argv + 4, argc - 4);
//    return (write_result(res.output, res.output_len), res.status);
//}

//ENTRYPOINT(handler)
#include "../include/stylus_sdk.h"
#include "../stylus-sdk-c/include/stylus_utils.h"
#include "../stylus-sdk-c/include/storage.h"
#include "../stylus-sdk-c/include/string.h"
#include <stdbool.h> // Por si se requiere bool (depende del entorno Stylus)

/**
 * Este contrato es un challenge de 4 preguntas.
 * - Solo el owner puede activar/desactivar el challenge y cambiar las preguntas.
 * - Los participantes deben responder las 4 preguntas en orden.
 * - Las primeras 5 personas en completarlo serán marcadas como ganadoras.
 */

// Configuraciones
#define MAX_WINNERS 5
#define MAX_STUDENTS 200
#define MAX_QUESTION_LEN 64
#define MAX_ANSWER_LEN 64

// Estructuras
typedef struct {
    uint8_t address[32];        // Dirección del estudiante (32 bytes)
    uint8_t current_question;   // Pregunta actual que debe responder (0-3)
} Student;

typedef struct {
    uint8_t owner[32];                // Owner del contrato
    bool active;                      // Si el reto está activo
    uint16_t winner_count;            // Cantidad de ganadores
    uint8_t winners[MAX_WINNERS][32]; // Lista de ganadores (hasta 5)
    Student students[MAX_STUDENTS];   // Lista de estudiantes
    char questions[4][MAX_QUESTION_LEN];
    char answers[4][MAX_ANSWER_LEN];
} Contract;

Contract contract;

// Funciones auxiliares de memoria y strings
static int	ft_memcmp(void *dest, void *src, size_t n) {
	unsigned char	*ptr1 = (unsigned char *)dest;
	unsigned char	*ptr2 = (unsigned char *)src;
	while (n--) {
		if (*ptr1 != *ptr2) return (*ptr1 - *ptr2);
		ptr1++;
		ptr2++;
	}
	return 0;
}

static void	ft_bzero(void *s, size_t n) {
	unsigned char	*ptr = (unsigned char *)s;
	while (n--) *ptr++ = 0;
}

static void	ft_memcpy(void *dest, void *src, size_t n) {
	unsigned char	*ptr1 = (unsigned char *)dest;
	unsigned char	*ptr2 = (unsigned char *)src;
	while (n--) *ptr1++ = *ptr2++;
}

static void	ft_strlcpy(char *dst, const char *src, size_t size) {
	size_t	i = 0;
	while (i < size - 1 && src[i]) {
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
}

static size_t	ft_strlen(const char *str) {
	size_t	len = 0;
	while (str[len]) len++;
	return len;
}

static int	ft_strcmp(const char *s1, const char *s2) {
	while (*s1 && *s1 == *s2) {
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

// Busca o crea un estudiante
static Student* find_or_create_student(uint8_t *student_address) {
    for (int i = 0; i < MAX_STUDENTS; i++) {
        if (ft_memcmp(contract.students[i].address, student_address, 32) == 0) {
            return &contract.students[i];
        }
    }

    // Crear nuevo registro si no existe
    for (int i = 0; i < MAX_STUDENTS; i++) {
        uint8_t empty[32];
        ft_bzero(empty, 32);
        if (ft_memcmp(contract.students[i].address, empty, 32) == 0) {
            ft_memcpy(contract.students[i].address, student_address, 32);
            contract.students[i].current_question = 0;
            return &contract.students[i];
        }
    }
    return NULL;
}

static bool is_owner(uint8_t *sender) {
    return (ft_memcmp(contract.owner, sender, 32) == 0);
}

// Retornos auxiliares
static ArbResult _return_bool(bool val) {
    static uint8_t data[32];
    ft_bzero(data, 32);
    // Si el valor es true, colocar 0x01 en el último byte
    if (val) data[31] = 0x01;
    ArbResult res = {Success, data, 32};
    return res;
}

static ArbResult _return_uint8(uint8_t val) {
    static uint8_t data[32];
    ft_bzero(data, 32);
    // Colocar el uint8 en el último byte
    data[31] = val;
    ArbResult res = {Success, data, 32};
    return res;
}

static ArbResult _return_winners() {
    size_t total_len = contract.winner_count * 32;
    uint8_t output[total_len];
    ft_bzero(output, total_len);

    for (int i = 0; i < contract.winner_count; i++) {
        ft_memcpy(output + (i * 32), contract.winners[i], 32);
    }

    ArbResult res = {Success, output, total_len};
    return res;
}

// Funciones del contrato
ArbResult init(uint8_t *input, size_t len) {
    uint8_t sender[32];
    msg_sender_padded(sender);

    ft_memcpy(contract.owner, sender, 32);
    contract.active = false;
    contract.winner_count = 0;

    // Preguntas y respuestas por defecto
    ft_strlcpy(contract.questions[0], "Who are you?", MAX_QUESTION_LEN);
    ft_strlcpy(contract.answers[0], "The one who knocks", MAX_ANSWER_LEN);

    ft_strlcpy(contract.questions[1], "Who creates Bitcoin?", MAX_QUESTION_LEN);
    ft_strlcpy(contract.answers[1], "Satoshi Nakamoto", MAX_ANSWER_LEN);

    ft_strlcpy(contract.questions[2], "What is the meaning of bit?", MAX_QUESTION_LEN);
    ft_strlcpy(contract.answers[2], "Binary digit", MAX_ANSWER_LEN);

    ft_strlcpy(contract.questions[3], "Which is the best way to learn code?", MAX_QUESTION_LEN);
    ft_strlcpy(contract.answers[3], "Coding", MAX_ANSWER_LEN);

    return _return_short_string(Success, "Contract initialized");
}

ArbResult set_active(uint8_t *input, size_t len) {
    uint8_t sender[32];
    msg_sender_padded(sender);

    if (!is_owner(sender)) {
        return _return_short_string(Failure, "Only owner");
    }
    if (len < 1) {
        return _return_short_string(Failure, "Missing bool");
    }

    bool val = (input[0] != 0);
    contract.active = val;
    return _return_short_string(Success, val ? "Activated" : "Deactivated");
}

ArbResult set_questions(uint8_t *input, size_t len) {
    uint8_t sender[32];
    msg_sender_padded(sender);

    if (!is_owner(sender)) {
        return _return_short_string(Failure, "Only owner");
    }

    // input formateado con 8 strings separadas por \0
    char *parts[8];
    char *ptr = (char*)input;
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if ((size_t)(ptr - (char*)input) >= len) {
            return _return_short_string(Failure, "Invalid input");
        }
        parts[i] = ptr;
        size_t slen = ft_strlen(ptr);
        ptr += (slen + 1);
        count++;
    }

    if (count < 8) {
        return _return_short_string(Failure, "Not enough input");
    }

    for (int i = 0; i < 4; i++) {
        ft_strlcpy(contract.questions[i], parts[i*2], MAX_QUESTION_LEN);
        ft_strlcpy(contract.answers[i], parts[i*2+1], MAX_ANSWER_LEN);
    }

    return _return_short_string(Success, "Questions set");
}

ArbResult is_active(uint8_t *input, size_t len) {
    return _return_bool(contract.active);
}

ArbResult get_current_question(uint8_t *input, size_t len) {
    if (len < 32) {
        return _return_short_string(Failure, "Missing address");
    }

    uint8_t student_address[32];
    ft_memcpy(student_address, input, 32);

    Student* student = find_or_create_student(student_address);
    if (!student) {
        return _return_short_string(Failure, "No student slot");
    }

    return _return_uint8(student->current_question);
}

ArbResult get_question_text(uint8_t *input, size_t len) {
    if (len < 1) {
        return _return_short_string(Failure, "No question id");
    }
    uint8_t q_id = input[0];
    if (q_id > 3) {
        return _return_short_string(Failure, "Invalid question id");
    }

    size_t slen = ft_strlen(contract.questions[q_id]);
    ArbResult res = {Success, (uint8_t*)contract.questions[q_id], slen};
    return res;
}

ArbResult verify_answer(uint8_t *input, size_t len) {
    uint8_t sender[32];
    msg_sender_padded(sender);

    if (!contract.active) {
        return _return_short_string(Failure, "Contract not active");
    }

    if (contract.winner_count >= MAX_WINNERS) {
        return _return_short_string(Failure, "Max winners reached");
    }

    if (len < 33) {
        return _return_short_string(Failure, "Invalid input");
    }

    uint8_t student_address[32];
    ft_memcpy(student_address, input, 32);
    char *answer = (char *)(input + 32);

    Student *student = find_or_create_student(student_address);
    if (!student) {
        return _return_short_string(Failure, "No student slot");
    }

    if (student->current_question >= 4) {
        return _return_short_string(Failure, "Already completed");
    }

    uint8_t q_id = student->current_question;
    if (ft_strcmp(answer, contract.answers[q_id]) == 0) {
        student->current_question++;
        if (student->current_question == 4) {
            ft_memcpy(contract.winners[contract.winner_count], student_address, 32);
            contract.winner_count++;
            return _return_short_string(Success, "Winner!");
        } else {
            return _return_short_string(Success, "Correct! Next question");
        }
    } else {
        return _return_short_string(Failure, "Wrong answer");
    }
}

ArbResult get_winners_fn(uint8_t *input, size_t len) {
    return _return_winners();
}

ArbResult is_winner_fn(uint8_t *input, size_t len) {
    if (len < 32) {
        return _return_short_string(Failure, "Invalid input");
    }

    uint8_t addr[32];
    ft_memcpy(addr, input, 32);

    for (int i = 0; i < contract.winner_count; i++) {
        if (ft_memcmp(contract.winners[i], addr, 32) == 0) {
            return _return_bool(true);
        }
    }
    return _return_bool(false);
}

ArbResult get_owner(uint8_t *input, size_t len) {
    ArbResult res = {Success, contract.owner, 32};
    return res;
}

// Registro de funciones

int handler(size_t argc) {
    uint8_t argv[argc];
    read_args(argv);

	FunctionRegistry registry[] = {
		{to_function_selector("init()"), init},
		{to_function_selector("set_active(bool)"), set_active},
		{to_function_selector("set_questions(string)"), set_questions},
		{to_function_selector("is_active()"), is_active},
		{to_function_selector("get_current_question(address)"), get_current_question},
		{to_function_selector("get_question_text(uint8)"), get_question_text},
		{to_function_selector("verify_answer(bytes)"), verify_answer},
		{to_function_selector("get_winners()"), get_winners_fn},
		{to_function_selector("is_winner(address)"), is_winner_fn},
		{to_function_selector("get_owner()"), get_owner},
	};

	uint32_t signature = *((uint32_t *)argv);

	ArbResult res = call_function(registry, sizeof(registry)/sizeof(registry[0]), signature, argv + 4, argc - 4);
	return (write_result(res.output, res.output_len), res.status);
}

ENTRYPOINT(handler)
