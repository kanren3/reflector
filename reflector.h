#ifndef _REFLECTOR_H_
#define _REFLECTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#define RINAPI __stdcall

#define REPAIR_NONE            0x00000000
#define REPAIR_REL             0x00000001
#define REPAIR_JCC             0x00000002
#define REPAIR_JMP             0x00000004
#define REPAIR_CALL            0x00000008

#define BRANCH_LOCAL           0x00010000
#define BRANCH_REMOTE          0x00020000
#define BRANCH_IMP             0x00040000

#define REGISTER_BITMAP_EAX     0x00000001
#define REGISTER_BITMAP_ECX     0x00000002
#define REGISTER_BITMAP_EDX     0x00000004
#define REGISTER_BITMAP_EBX     0x00000008
#define REGISTER_BITMAP_ESI     0x00000010
#define REGISTER_BITMAP_EDI     0x00000020
#define REGISTER_BITMAP_EBP     0x00000040

    typedef struct _ANALYZER {
        struct {
            PUCHAR Address;
            ZyanUSize Length;
            ZydisDecodedInstruction Instruction;
            ZydisDecodedOperand Operands[ZYDIS_MAX_OPERAND_COUNT];
        }Decoded;
        struct {
            PUCHAR Address;
            ZyanUSize Length;
            ZydisEncoderRequest Request;
        }Encoder;
        struct {
            ULONG Flags;
            ULONG Index;
            PUCHAR Address;
        }Repair;
    }ANALYZER, * PANALYZER;

    typedef
        PVOID
        (RINAPI * REPAIR_CALLBACK)(
            __in ULONG Flags,
            __in_opt PVOID Address
            );

    BOOLEAN
        RINAPI
        InitializeReflector(
            VOID
        );

    PVOID
        RINAPI
        RinAllocateMemory(
            __in ULONG Length
        );

    VOID
        RINAPI
        RinFreeMemory(
            __in PVOID Pointer
        );

    PVOID
        RINAPI
        RinReflector(
            __in PUCHAR Address,
            __in ULONG Length,
            __in ULONG Multiple,
            __in_opt REPAIR_CALLBACK Callback
        );

#ifdef __cplusplus
}
#endif

#endif
