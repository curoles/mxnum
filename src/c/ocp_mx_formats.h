/**@file
 * @brief OCP Microscaling Formats.
 * @author Igor Lesik
 * @copyright Igor Lesik 2024
 *
 * References:
 * - https://www.opencompute.org/documents/ocp-microscaling-formats-mx-v1-0-spec-final-pdf
 *
 */
#pragma once

typedef enum MxFormatType {
    MX_FORMAT_MXFP8,
    MX_FORMAT_MXFP6,
    MX_FORMAT_MXFP4,
    MX_FORMAT_MXINT8,
} MxFormatType;

typedef enum MxElementType {
    MX_ELEM_FP8_E5M2,
    MX_ELEM_FP8_E4M3,
} MxElementType;

typedef enum MxScaleType {
    MX_SCALE_E8M0,
} MxScaleType;

typedef struct MxFormat {
    MxFormatType fmt_type;
    MxElementType elem_type;
    MxScaleType scale_type;
    uint8_t scale_width;
    uint8_t elem_width;
    uint8_t block_size;
} MxFormat;

#define DEF_MX_FORMATS \
DEF_MX_FMT(MXFP8,  FP8_E5M2, E8M0, 8, 8, 32) \
DEF_MX_FMT(MXFP8,  FP8_E4M3, E8M0, 8, 8, 32) \
DEF_MX_FMT(MXFP6,  FP6_E3M2, E8M0, 8, 6, 32) \
DEF_MX_FMT(MXFP6,  FP6_E2M3, E8M0, 8, 6, 32) \
DEF_MX_FMT(MXFP4,  FP4_E2M1, E8M0, 8, 4, 32) \
DEF_MX_FMT(MXINT8, INT8,     E8M0, 8, 8, 32)

static inline
MxFormat make_mxfp8_e5m2(void) {
    return (MxFormat) {
        .fmt_type = MX_FORMAT_MXFP8,
        .elem_type = MX_ELEM_FP8_E5M2,
        .scale_type = MX_SCALE_E8M0,
        .scale_width = 8,
        .elem_width = 8,
        .block_size = 32
    };
}