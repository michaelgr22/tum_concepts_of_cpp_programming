#include <climits>
#include <cstdint>
#include <print>

extern void division_by_zero();
int32_t next();

namespace simplevm {
int32_t execute() {
    int32_t reg[4] = {0, 0, 0, 0};

    int32_t opcode = next();
    while (opcode != 0) {
        switch (opcode) {
            case 10: {
                int32_t ireg = next();
                int32_t iimm = next();
                reg[ireg] = iimm;
                break;
            }
            case 20: {
                int32_t ireg = next();
                reg[0] = reg[ireg];
                break;
            }
            case 21: {
                int32_t ireg = next();
                reg[ireg] = reg[0];
                break;
            }
            case 22: {
                int32_t tmp = reg[0];
                reg[0] = reg[1];
                reg[1] = tmp;
                break;
            }
            case 50: {
                reg[0] = reg[0] + reg[1];
                break;
            }
            case 51: {
                reg[0] = reg[0] - reg[1];
            } break;
            case 53: {
                reg[0] = reg[0] * reg[1];
            } break;
            case 54: {
                if (reg[1] == 0) {
                    division_by_zero();
                    return 0;
                }
                int32_t remainder = reg[0] % reg[1];
                reg[0] = reg[0] / reg[1];
                reg[1] = remainder;
                break;
            }
            default:
                break;
        }
        opcode = next();
    }
    return reg[0];
}
} // namespace simplevm