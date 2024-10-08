#pragma once
#define GAME_API_BASE 500

// System calls written in assembly
#define ECALL_PRINT (GAME_API_BASE + 0)
#define ECALL_VCALL (GAME_API_BASE + 1)
#define ECALL_VEVAL (GAME_API_BASE + 2)
#define ECALL_VFREE (GAME_API_BASE + 3)
#define ECALL_GET_OBJ (GAME_API_BASE + 4) // Get an object by name
#define ECALL_OBJ (GAME_API_BASE + 5) // All the Object functions
#define ECALL_OBJ_CALLP (GAME_API_BASE + 6) // Call a method on an object
#define ECALL_GET_NODE (GAME_API_BASE + 7) // Get a node by path
#define ECALL_NODE (GAME_API_BASE + 8) // All the Node functions
#define ECALL_NODE2D (GAME_API_BASE + 9) // All the Node2D functions
#define ECALL_NODE3D (GAME_API_BASE + 10) // All the Node3D functions

#define ECALL_THROW (GAME_API_BASE + 11)
#define ECALL_IS_EDITOR (GAME_API_BASE + 12)

#define ECALL_LAST (GAME_API_BASE + 13)

#define STRINGIFY_HELPER(x) #x
#define STRINGIFY(x) STRINGIFY_HELPER(x)

#define MAKE_SYSCALL(number, rval, name, ...)                      \
	__asm__(".pushsection .text\n"                                 \
			".global " #name "\n"                                  \
			".type " #name ", @function\n"                         \
			"" #name ":\n"                                         \
			"	li a7, " STRINGIFY(number) "\n"                    \
										   "   ecall\n"            \
										   "   ret\n"              \
										   ".popsection .text\n"); \
	extern "C" rval name(__VA_ARGS__);

#define EXTERN_SYSCALL(number, rval, name, ...) \
	extern "C" rval name(__VA_ARGS__);

enum class Object_Op {
	GET_METHOD_LIST,
	GET,
	SET,
	GET_PROPERTY_LIST,
	CONNECT,
	DISCONNECT,
	GET_SIGNAL_LIST,
};

enum class Node_Op {
	GET_NAME = 0,
	GET_PATH,
	GET_PARENT,
	QUEUE_FREE,
	DUPLICATE,
	GET_CHILD_COUNT,
	GET_CHILD,
	ADD_CHILD,
	ADD_CHILD_DEFERRED,
	ADD_SIBLING,
	ADD_SIBLING_DEFERRED,
	MOVE_CHILD,
	REMOVE_CHILD,
	REMOVE_CHILD_DEFERRED,
	GET_CHILDREN,
};

enum class Node2D_Op {
	GET_POSITION = 0,
	SET_POSITION,
	GET_ROTATION,
	SET_ROTATION,
	GET_SCALE,
	SET_SCALE,
	GET_SKEW,
	SET_SKEW,
	GET_TRANSFORM,
	SET_TRANSFORM,
};

enum class Node3D_Op {
	GET_POSITION = 0,
	SET_POSITION,
	GET_ROTATION,
	SET_ROTATION,
	GET_SCALE,
	SET_SCALE,
	GET_TRANSFORM,
	SET_TRANSFORM,
	GET_QUATERNION,
	SET_QUATERNION,
};
