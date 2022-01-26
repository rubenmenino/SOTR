/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _TASKMANAGER_H    /* Guard against multiple inclusion */
#define _TASKMANAGER_H

void TMAN_Init(void);
void TMAN_Close(void);
void TMAN_TaskAdd(void);
void TMAN_TaskRegisterAtributes(void);
void TMAN_TaskWaitPeriod(void);
void TMAN_TaskStats(void);

#endif _TASKMANAGER_H