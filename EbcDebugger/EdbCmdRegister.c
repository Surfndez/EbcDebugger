/*++

Copyright (c) 2007, Intel Corporation                                                         
All rights reserved. This program and the accompanying materials                          
are licensed and made available under the terms and conditions of the BSD License         
which accompanies this distribution.  The full text of the license may be found at        
http://opensource.org/licenses/bsd-license.php                                            
                                                                                          
THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

Module Name:

  EdbCmdRegister.c
  
Abstract:


--*/

#include "Edb.h"

EFI_DEBUG_STATUS
DebuggerRegister (
  IN     CHAR16                    *CommandArg,
  IN     EFI_DEBUGGER_PRIVATE_DATA *DebuggerPrivate,
  IN     EFI_EXCEPTION_TYPE        ExceptionType,
  IN OUT EFI_SYSTEM_CONTEXT        SystemContext
  )
/*++

Routine Description:

  DebuggerCommand - Register
  
Arguments:

  CommandArg      - The argument for this command
  DebuggerPrivate - EBC Debugger private data structure
  InterruptType   - Interrupt type.
  SystemContext   - EBC system context.

Returns:

  EFI_DEBUG_CONTINUE - formal return value
  
--*/
{
  CHAR16  *RegName;
  CHAR16  *RegValStr;
  UINT64  RegVal;

  //
  // Check Argument, NULL means print all register
  //
  if (CommandArg == 0) {
    EDBPrint (
      L"  R0 - 0x%016lx, R1 - 0x%016lx\n",
      SystemContext.SystemContextEbc->R0,
      SystemContext.SystemContextEbc->R1
      );
    EDBPrint (
      L"  R2 - 0x%016lx, R3 - 0x%016lx\n",
      SystemContext.SystemContextEbc->R2,
      SystemContext.SystemContextEbc->R3
      );
    EDBPrint (
      L"  R4 - 0x%016lx, R5 - 0x%016lx\n",
      SystemContext.SystemContextEbc->R4,
      SystemContext.SystemContextEbc->R5
      );
    EDBPrint (
      L"  R6 - 0x%016lx, R7 - 0x%016lx\n",
      SystemContext.SystemContextEbc->R6,
      SystemContext.SystemContextEbc->R7
      );
    EDBPrint (
      L"  Flags - 0x%016lx, ControlFlags - 0x%016lx\n",
      SystemContext.SystemContextEbc->Flags,
      SystemContext.SystemContextEbc->ControlFlags
      );
    EDBPrint (
      L"  Ip - 0x%016lx\n",
      SystemContext.SystemContextEbc->Ip
      );
    return EFI_DEBUG_CONTINUE;
  }

  //
  // Get register name
  //
  RegName = CommandArg;
  //
  // Get register value
  //
  RegValStr = StrGetNextTokenLine (L" ");
  if (RegValStr == NULL) {
    EDBPrint (L"Invalid Register Value\n");
    return EFI_DEBUG_CONTINUE;
  }
  RegVal = LXtoi (RegValStr);

  //
  // Assign register value
  //
  if (StriCmp (RegName, L"R0") == 0) {
    SystemContext.SystemContextEbc->R0 = RegVal;
  } else if (StriCmp (RegName, L"R1") == 0) {
    SystemContext.SystemContextEbc->R1 = RegVal;
  } else if (StriCmp (RegName, L"R2") == 0) {
    SystemContext.SystemContextEbc->R2 = RegVal;
  } else if (StriCmp (RegName, L"R3") == 0) {
    SystemContext.SystemContextEbc->R3 = RegVal;
  } else if (StriCmp (RegName, L"R4") == 0) {
    SystemContext.SystemContextEbc->R4 = RegVal;
  } else if (StriCmp (RegName, L"R5") == 0) {
    SystemContext.SystemContextEbc->R5 = RegVal;
  } else if (StriCmp (RegName, L"R6") == 0) {
    SystemContext.SystemContextEbc->R6 = RegVal;
  } else if (StriCmp (RegName, L"R7") == 0) {
    SystemContext.SystemContextEbc->R7 = RegVal;
  } else if (StriCmp (RegName, L"Flags") == 0) {
    SystemContext.SystemContextEbc->Flags = RegVal;
  } else if (StriCmp (RegName, L"ControlFlags") == 0) {
    SystemContext.SystemContextEbc->ControlFlags = RegVal;
  } else if (StriCmp (RegName, L"Ip") == 0) {
    SystemContext.SystemContextEbc->Ip = RegVal;
  } else {
    EDBPrint (L"Invalid Register - %s\n", RegName);
  }

  //
  // Done
  //
  return EFI_DEBUG_CONTINUE;
}
