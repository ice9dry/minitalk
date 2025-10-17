#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

CLIENT="./client"
SERVER_PID=$1

if [ -z "$SERVER_PID" ]; then
    echo -e "${RED}Usage: $0 <server_pid>${NC}"
    exit 1
fi

if [ ! -f "$CLIENT" ]; then
    echo -e "${RED}Error: Client binary '$CLIENT' not found${NC}"
    exit 1
fi

echo -e "${YELLOW}Testing minitalk with server PID: $SERVER_PID${NC}"
echo "=========================================="

# Test function
test_string() {
    local test_name="$1"
    local string="$2"

    echo -e "${YELLOW}Testing: $test_name${NC}"
    echo "Length: ${#string} characters"

    # Send string via client
    $CLIENT $SERVER_PID "$string"

    if [ $? -eq 0 ]; then
        echo -e "${GREEN}✓ Sent successfully${NC}"
    else
        echo -e "${RED}✗ Failed to send${NC}"
    fi
    echo ""
}

# Test different string lengths
test_string "Empty string" ""
test_string "Single character" "A"
test_string "Short string" "Hello"
test_string "Medium string" "This is a test string of medium length"
test_string "Long string" "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation."

# Power of 2 lengths
test_string "2 characters" "AB"
test_string "4 characters" "ABCD"
test_string "8 characters" "12345678"
test_string "16 characters" "16-char-string!!!!"
test_string "32 characters" "This-is-exactly-thirty-two-chars!!"
test_string "64 characters" "This string is exactly sixty-four characters long which is 2^6!!"
test_string "128 characters" "This string is exactly one hundred twenty-eight characters long, which is 2^7 and should be a good test for the minitalk project implementation!"

# Very long strings
test_string "256 characters" "This is a 256 character string. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Phasellus imperdiet, nulla et dictum interdum, nisi lorem egestas odio, vitae scelerisque enim ligula venenatis dolor. Maecenas nisl est, ultrices nec congue eget, auctor vitae massa. Fusce luctus vestibulum."

test_string "512 characters" "This is a 512 character string. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. This is the end of the 512 character test string."

test_string "1024 characters" "This is a 512 character string. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. This is the end of the 512 character test string. This is a 512 character string. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. This is the end of the 512 character test string."
# Special characters
test_string "Newlines" $'Line1\nLine2\nLine3'
test_string "Tabs and spaces" "Hello\tWorld  Test"
test_string "Mixed special chars" "Test\x00Null\tTab\nNewline"

echo -e "${GREEN}All tests completed!${NC}"