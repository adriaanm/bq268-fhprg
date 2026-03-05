/* xml.c — XML parser & writer for Firehose protocol.
 *
 * The parser is a simple state machine tokenizer that processes XML
 * character-by-character. The writer builds XML strings into a buffer.
 *
 * Source: src/fhprg/fhprg_8037820.c (0x08038xxx–0x08039xxx range)
 */
#include "firehose.h"

/*------------------------------------------------------------------------
 * XML Parser
 *------------------------------------------------------------------------*/

/* orig: 0x08038c24 xml_send_and_wait — send XML and wait for completion */
uint xml_send_and_wait(param_1, param_2, param_3)
uint param_1; uint param_2; uint param_3;
{
    DAT_08055f99 = '\0';
    send_and_wait(param_1, param_3, (uint)&LAB_08028888, (uint)&DAT_08055f88);
    while (DAT_08055f99 == '\0') {
        dispatch_loop_tick();
    }
    return 0;
}

/* Label reference — attr parser callback address */
extern char LAB_08028888;

/* orig: 0x08038cfa xml_get_attr_name — get attribute name from parser state */
bool xml_get_attr_name(param_1, param_2, param_3, param_4)
int *param_1; int param_2; uint param_3; uint param_4;
{
    uint uVar3 = param_1[0xe];
    uint uVar2 = param_1[0x10] - uVar3;
    uint uVar1 = ((param_1[0x11] - param_1[0xf]) - (uint)((uint)param_1[0x10] < uVar3)) +
                 (uint)(0xfffffffe < uVar2);
    bool bVar4 = uVar1 < param_4 || param_4 - uVar1 < (uint)(uVar2 + 1 <= param_3);
    if (bVar4) {
        bounded_memcpy(param_2, param_3, *param_1 + uVar3, uVar2);
        *(undefined1 *)(param_2 + uVar2) = 0;
    }
    return bVar4;
}

/* orig: 0x08038d38 xml_get_attr_value — get attribute value from parser state */
bool xml_get_attr_value(param_1, param_2, param_3, param_4)
int *param_1; int param_2; uint param_3; uint param_4;
{
    uint uVar3 = param_1[0x12];
    uint uVar2 = param_1[0x14] - uVar3;
    uint uVar1 = ((param_1[0x15] - param_1[0x13]) - (uint)((uint)param_1[0x14] < uVar3)) +
                 (uint)(0xfffffffe < uVar2);
    bool bVar4 = uVar1 < param_4 || param_4 - uVar1 < (uint)(uVar2 + 1 <= param_3);
    if (bVar4) {
        bounded_memcpy(param_2, param_3, *param_1 + uVar3, uVar2);
        *(undefined1 *)(param_2 + uVar2) = 0;
    }
    return bVar4;
}

/* orig: 0x08038d76 xml_get_tag_name — get tag name from parser state */
bool xml_get_tag_name(param_1, param_2, param_3, param_4)
int *param_1; int param_2; uint param_3; uint param_4;
{
    uint uVar3 = param_1[10];
    uint uVar2 = param_1[0xc] - uVar3;
    uint uVar1 = ((param_1[0xd] - param_1[0xb]) - (uint)((uint)param_1[0xc] < uVar3)) +
                 (uint)(0xfffffffe < uVar2);
    bool bVar4 = uVar1 < param_4 || param_4 - uVar1 < (uint)(uVar2 + 1 <= param_3);
    if (bVar4) {
        bounded_memcpy(param_2, param_3, *param_1 + uVar3, uVar2);
        *(undefined1 *)(param_2 + uVar2) = 0;
    }
    return bVar4;
}

/* orig: 0x08038db4 xml_advance — XML tokenizer state machine.
 *
 * Advances through the XML buffer one character at a time. Returns:
 *   0 = no token yet (or whitespace/error)
 *   1 = open tag found
 *   2 = attribute found
 *   3 = text content found
 *   4 = close tag found
 *   5 = comment end found
 */
int xml_advance(param_1)
int *param_1;
{
    char cVar1;
    byte bVar2;
    bool bVar3;
    undefined1 uVar4;
    int *piVar5;
    int iVar6;
    int iVar7;
    uint uVar8;
    uint uVar9;
    uint uVar10;
    int iVar11;
    uint uVar12;
    uint uVar13;

    iVar11 = 0;
    bVar3 = false;
    uVar13 = param_1[2];
    uVar12 = param_1[3];
    do {
        uVar9 = param_1[6];
        uVar10 = param_1[7];
        if (uVar12 < uVar10 || uVar10 - uVar12 < (uint)(uVar13 <= uVar9)) {
            return iVar11;
        }
        iVar6 = *param_1;
        cVar1 = (char)param_1[4];
        uVar8 = (uint)*(byte *)(iVar6 + uVar9);
        if (cVar1 == '\0') {
            if (uVar8 == 0x3c) {
                if (param_1[8] == 0 && param_1[9] == 0) {
                    uVar4 = 1;
                } else {
LAB_08038e30:
                    uVar4 = 5;
                }
LAB_08038ff2:
                *(undefined1 *)(param_1 + 4) = uVar4;
            } else {
                piVar5 = (int *)get_ctype_table();
                bVar2 = *(byte *)(*piVar5 + uVar8);
LAB_08038f3e:
                if ((bVar2 & 1) == 0) {
LAB_08038f40:
                    bVar3 = true;
                }
            }
        }
        else if (cVar1 == '\x01') {
            piVar5 = (int *)get_ctype_table();
            if (((*(byte *)(*piVar5 + uVar8) & 0x98) == 0) && (uVar8 != 0x3f)) {
                if (uVar8 != 0x21) goto LAB_08038f40;
LAB_08038e50:
                uVar4 = 0xe;
                goto LAB_08038ff2;
            }
LAB_08038e4c:
            uVar4 = 2;
LAB_08038efe:
            *(undefined1 *)(param_1 + 4) = uVar4;
            param_1[10] = uVar9;
            param_1[0xb] = uVar10;
        }
        else if (cVar1 == '\x02') {
            if (uVar8 == 0x3e) {
                uVar4 = 3;
            } else {
                piVar5 = (int *)get_ctype_table();
                if ((*(byte *)(*piVar5 + uVar8) & 1) == 0) {
                    if ((*(byte *)(*piVar5 + uVar8) & 0x38) != 0) goto LAB_08038ff4;
                    if (uVar8 != 0x2f) goto LAB_08038f40;
                    uVar4 = 8;
                } else {
                    uVar4 = 9;
                }
            }
            *(undefined1 *)(param_1 + 4) = uVar4;
            param_1[0xc] = uVar9;
            param_1[0xd] = uVar10;
            iVar11 = 1;
            iVar6 = param_1[8] + 1;
            iVar7 = param_1[9] + (uint)(0xfffffffe < (uint)param_1[8]);
LAB_08038f5c:
            param_1[8] = iVar6;
            param_1[9] = iVar7;
        }
        else if (cVar1 == '\x03') {
            piVar5 = (int *)get_ctype_table();
            if ((*(byte *)(*piVar5 + uVar8) & 0x98) == 0) {
                if (uVar8 == 0x3c) goto LAB_08038e30;
            } else {
                *(undefined1 *)(param_1 + 4) = 4;
                param_1[0x16] = uVar9;
                param_1[0x17] = uVar10;
            }
        }
        else if (cVar1 == '\x04') {
            if (uVar8 == 0x3c) {
                iVar11 = 3;
                *(undefined1 *)(param_1 + 4) = 5;
            }
        }
        else if (cVar1 == '\x05') {
            if (uVar8 == 0x2f) {
                uVar4 = 6;
                goto LAB_08038ff2;
            }
            piVar5 = (int *)get_ctype_table();
            if ((*(byte *)(*piVar5 + uVar8) & 0x98) != 0) goto LAB_08038e4c;
            if (uVar8 == 0x21) goto LAB_08038e50;
        }
        else if (cVar1 == '\x06') {
            piVar5 = (int *)get_ctype_table();
            if ((*(byte *)(*piVar5 + uVar8) & 0x98) != 0) {
                uVar4 = 7;
                goto LAB_08038efe;
            }
        }
        else if (cVar1 == '\a') {
            if (uVar8 == 0x3e) {
                *(undefined1 *)(param_1 + 4) = 0;
                param_1[0xc] = uVar9;
                param_1[0xd] = uVar10;
LAB_08038f52:
                iVar11 = 4;
                iVar6 = param_1[8] + -1;
                iVar7 = param_1[9] + -1 + (uint)(param_1[8] != 0);
                goto LAB_08038f5c;
            }
        }
        else if (cVar1 == '\t') {
            if ((uVar8 == 0x2f) || (uVar8 == 0x3f)) {
                uVar4 = 8;
                goto LAB_08038ff2;
            }
            piVar5 = (int *)get_ctype_table();
            bVar2 = *(byte *)(*piVar5 + uVar8);
            if ((bVar2 & 0x98) == 0) goto LAB_08038f3e;
            *(undefined1 *)(param_1 + 4) = 10;
            param_1[0xe] = uVar9;
            param_1[0xf] = uVar10;
        }
        else if (cVar1 == '\b') {
            if (uVar8 == 0x3e) {
                *(undefined1 *)(param_1 + 4) = 0;
                goto LAB_08038f52;
            }
        }
        else if (cVar1 == '\n') {
            if (uVar8 == 0x3d) {
                *(undefined1 *)(param_1 + 4) = 0xb;
                param_1[0x10] = uVar9;
                param_1[0x11] = uVar10;
            }
        }
        else if (cVar1 == '\v') {
            if (uVar8 == 0x22) {
                uVar4 = 0xc;
                goto LAB_08038ff2;
            }
        }
        else {
            if (cVar1 == '\f') {
                *(undefined1 *)(param_1 + 4) = 0xd;
                param_1[0x12] = uVar9;
                param_1[0x13] = uVar10;
            }
            else if (cVar1 != '\r') {
                if (cVar1 == '\x0e') {
                    if (uVar8 == 0x2d) {
                        uVar8 = uVar9 + 1;
                        uVar10 = uVar10 + (0xfffffffe < uVar9);
                        param_1[6] = uVar8;
                        param_1[7] = uVar10;
                        if ((uVar10 <= uVar12 && (uint)(uVar13 <= uVar8) <= uVar10 - uVar12) &&
                           (*(char *)(iVar6 + uVar8) == '-')) {
                            uVar4 = 0xf;
                            goto LAB_08038ff2;
                        }
                    }
                }
                else if (cVar1 == '\x0f') {
                    *(undefined1 *)(param_1 + 4) = 0x10;
                    param_1[0x1a] = uVar9;
                    param_1[0x1b] = uVar10;
                }
                else if (cVar1 == '\x10') {
                    if (uVar8 == 0x2d) {
                        *(undefined1 *)(param_1 + 4) = 0x11;
                        param_1[0x1c] = uVar9;
                        param_1[0x1d] = uVar10;
                    }
                }
                else if (cVar1 == '\x11') {
                    if (uVar8 == 0x2d) {
                        uVar8 = uVar9 + 1;
                        uVar10 = uVar10 + (0xfffffffe < uVar9);
                        param_1[6] = uVar8;
                        param_1[7] = uVar10;
                        if ((uVar10 <= uVar12 && (uint)(uVar13 <= uVar8) <= uVar10 - uVar12) &&
                           (*(char *)(iVar6 + uVar8) == '>')) {
                            iVar11 = 5;
                            *(undefined1 *)(param_1 + 4) = 0;
                            goto LAB_08038ff4;
                        }
                    }
                    uVar4 = 0x10;
                    goto LAB_08038ff2;
                }
                goto LAB_08038ff4;
            }
            if (uVar8 == 0x22) {
                *(undefined1 *)(param_1 + 4) = 9;
                param_1[0x14] = uVar9;
                param_1[0x15] = uVar10;
                iVar11 = 2;
            }
        }
LAB_08038ff4:
        uVar10 = param_1[6];
        param_1[6] = uVar10 + 1;
        param_1[7] = param_1[7] + (uint)(0xfffffffe < uVar10);
        if (iVar11 != 0) {
            return iVar11;
        }
        if (bVar3) {
            return 0;
        }
    } while (true);
}

/*------------------------------------------------------------------------
 * XML Attribute/Tag Matching
 *------------------------------------------------------------------------*/

/* orig: 0x0803906c xml_attr_match — match attribute name (case-insensitive) */
uint xml_attr_match(param_1, param_2)
int *param_1; int param_2;
{
    int iVar3 = param_1[0xe];
    int iVar2 = param_1[0x10];
    int iVar1 = strncasecmp_fh((uint8_t *)param_2, (uint8_t *)(*param_1 + param_1[0xe]), 0);
    if ((iVar1 == 0) && (*(char *)(param_2 + (iVar2 - iVar3)) == '\0')) {
        return 1;
    }
    return 0;
}

/* orig: 0x08039092 xml_tag_match — match tag name (case-insensitive) */
uint xml_tag_match(param_1, param_2)
int *param_1; int param_2;
{
    int iVar3 = param_1[10];
    int iVar2 = param_1[0xc];
    int iVar1 = strncasecmp_fh((uint8_t *)param_2, (uint8_t *)(*param_1 + param_1[10]), 0);
    if ((iVar1 == 0) && (*(char *)(param_2 + (iVar2 - iVar3)) == '\0')) {
        return 1;
    }
    return 0;
}

/*------------------------------------------------------------------------
 * XML Writer
 *------------------------------------------------------------------------*/

/* orig: 0x080390d8 xml_wr_close_self — write self-closing " />" */
void xml_wr_close_self(param_1)
uint param_1;
{
    xml_wr_attr_start(param_1, (uint)&DAT_080390e0);
}

/* orig: 0x080390e4 xml_wr_close_tag — write closing tag "</%s>" */
void xml_wr_close_tag(param_1, param_2)
uint param_1; uint param_2;
{
    xml_wr_attr_start(param_1, (uint)"</%s>", param_2);
}

/* orig: 0x080390f4 xml_wr_tag_name — write element name "<%s" */
void xml_wr_tag_name(param_1, param_2)
uint param_1; uint param_2;
{
    xml_wr_attr_start(param_1, (uint)&DAT_080390fc, param_2);
}

/* orig: 0x08039100 xml_wr_open_tag — write open tag "<%s " */
void xml_wr_open_tag(param_1, param_2)
uint param_1; uint param_2;
{
    xml_wr_attr_start(param_1, (uint)&DAT_08039108, param_2);
}

/* orig: 0x08039110 xml_wr_attr_start — variadic write to XML buffer.
 * In the original, this is a 4-arg function that stuffs args 3+4 into
 * a local array and calls xml_wr_attr with a va_list pointer.
 * We implement it as a true variadic. */
void xml_wr_attr_start(param_1, param_2, param_3, param_4)
uint param_1; uint param_2; uint param_3; uint param_4;
{
    uint uStack_8;
    uint uStack_4;

    uStack_8 = param_3;
    uStack_4 = param_4;
    xml_wr_attr((int *)param_1, param_2, (uint)&uStack_8);
}

/* orig: 0x08039122 xml_wr_attr — vsnprintf into XML writer buffer */
uint xml_wr_attr(param_1, param_2, param_3)
int *param_1; uint param_2; uint param_3;
{
    uint uVar1;
    uint uVar2;
    uint uVar3;
    uint uVar4;

    if ((uint)param_1[5] <= (uint)param_1[3] &&
        (uint)((uint)param_1[2] <= (uint)param_1[4]) <= (uint)(param_1[5] - param_1[3])) {
        uVar1 = vsnprintf_wrapper((char *)(param_1[4] + *param_1), param_1[2] - param_1[4], (const char *)param_2, (va_list *)param_3);
        uVar2 = param_1[4];
        uVar3 = (param_1[3] - param_1[5]) - (uint)((uint)param_1[2] < uVar2);
        uVar4 = (int)uVar1 >> 0x1f;
        if (uVar4 <= uVar3 && (uint)(param_1[2] - uVar2 <= uVar1) <= uVar4 - uVar3) {
            param_1[4] = uVar2 + uVar1;
            param_1[5] = param_1[5] + uVar4 + (uint)CARRY4(uVar2, uVar1);
            return 1;
        }
    }
    return 0;
}

/* orig: 0x08039174 xml_wr_attr_quoted — write quoted attribute: ' name="value"' */
void xml_wr_attr_quoted(param_1, param_2, param_3)
uint param_1; uint param_2; uint param_3;
{
    xml_wr_attr_start(param_1, (uint)" %s=\"%s\"", param_2, param_3);
}

/* orig: 0x0803918c xml_wr_attr_value — write attribute with size check */
bool xml_wr_attr_value(param_1, param_2, param_3, param_4, param_5, param_6)
int param_1; uint param_2; uint param_3; uint param_4; uint param_5; int param_6;
{
    uint uVar1;
    uint uVar2;
    bool bVar3;

    uVar1 = strlen((char *)param_2);
    uVar2 = uVar1 + *(uint *)(param_1 + 0x10);
    uVar1 = *(int *)(param_1 + 0x14) + (uint)CARRY4(uVar1, *(uint *)(param_1 + 0x10)) +
             param_6 + (uint)(0xfffffffb < param_5) + (uint)CARRY4(uVar2, param_5 + 4);
    bVar3 = uVar1 < *(uint *)(param_1 + 0xc) ||
             *(uint *)(param_1 + 0xc) - uVar1 < (uint)(uVar2 + param_5 + 4 <= *(uint *)(param_1 + 8));
    if (bVar3) {
        xml_wr_attr_start(param_1, (uint)&DAT_080391e8, param_2);
        xml_wr_init((int *)(param_1), param_3, param_5, param_6);
        xml_wr_attr_start(param_1, (uint)&DAT_080391ec);
    }
    return bVar3;
}

/* orig: 0x080391f0 xml_wr_init — append raw bytes to XML writer buffer */
uint xml_wr_init(param_1, param_2, param_3, param_4)
int *param_1; uint param_2; uint param_3; int param_4;
{
    uint uVar1;

    uVar1 = param_1[5] + param_4 + (uint)CARRY4(param_1[4], param_3);
    if ((uint)param_1[3] <= uVar1 &&
        (uint)(param_1[4] + param_3 <= (uint)param_1[2]) <= param_1[3] - uVar1) {
        return 0;
    }
    bounded_memcpy(*param_1 + param_1[4], param_1[2], param_2, param_3);
    uVar1 = param_1[4];
    param_1[4] = uVar1 + param_3;
    param_1[5] = param_1[5] + param_4 + (uint)CARRY4(uVar1, param_3);
    return 1;
}

/* orig: 0x08039234 xml_wr_reset — reset XML writer state */
void xml_wr_reset(param_1)
int param_1;
{
    *(uint *)(param_1 + 0x10) = 0;
    *(uint *)(param_1 + 0x14) = 0;
    *(undefined1 *)(param_1 + 0x18) = 0;
    *(uint *)(param_1 + 0x40) = 0;
    *(uint *)(param_1 + 0x44) = 0;
    *(uint *)(param_1 + 0x48) = 0;
    *(uint *)(param_1 + 0x4c) = 0;
    *(uint *)(param_1 + 0x50) = *(uint *)(param_1 + 0x10);
    *(uint *)(param_1 + 0x54) = *(uint *)(param_1 + 0x14);
    *(undefined1 *)(param_1 + 0x58) = *(undefined1 *)(param_1 + 0x18);
    *(uint *)(param_1 + 0x60) = *(uint *)(param_1 + 0x40);
    *(uint *)(param_1 + 100) = *(uint *)(param_1 + 0x44);
    *(uint *)(param_1 + 0x68) = *(uint *)(param_1 + 0x48);
    *(uint *)(param_1 + 0x6c) = *(uint *)(param_1 + 0x4c);
}
