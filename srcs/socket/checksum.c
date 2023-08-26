# include "ft_traceroute.h"

/**
 * @brief Calculate ICMP Checksum
 *
 * Calculates the checksum value for ICMP packets based on the data and length provided.
 * This function is typically used to compute the checksum for the ICMP header and payload.
 *
 * @param data Pointer to the data for which the checksum is to be calculated.
 * @param length Length of the data in bytes.
 * @return The calculated ICMP checksum as a 16-bit unsigned integer.
*/
uint16_t calculate_icmp_checksum(void *data, size_t length)
{
    const uint16_t *buf = data;
    uint32_t sum;

    sum = 0;
    while (length > 1) {
        sum += *buf++;
        length -= 2;
    }

    /* Add the remaining byte, if present */
    if (length > 0) {
        sum += *(uint8_t *)buf;
    }

    /* Fold the carry bits to get a 16-bit result */
    while (sum >> 16) {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }

    /* Take the one's complement of the sum */
    return (uint16_t)~sum;
}