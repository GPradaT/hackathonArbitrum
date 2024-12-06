#include "../include/stylus_sdk.h"
#include "../stylus-sdk-c/include/stylus_utils.h"
#include "../stylus-sdk-c/include/storage.h"
#include "../stylus-sdk-c/include/string.h"

/**
 * General utils/helpers
 */

// buffer used to write output, avoiding malloc
uint8_t buf_out[32];

// succeed and return a bebi32
ArbResult inline _return_success_bebi32(bebi32 const retval)
{
  ArbResult res = {Success, retval, 32};
  return res;
}

bool inline is_valid_address(uint8_t *input, size_t len)
{
  // validate input is an address padded to 32 bytes
  if (len != 32)
    return false;

  if (!bebi32_is_u160(input))
    return false;

  return true;
}

ArbResult calldata_len(uint8_t *input, size_t len)
{
  bebi32_set_u32(buf_out, len);
  return _return_success_bebi32(buf_out);
}

char *ft_strnstr(const char *haystack, const char *needle, size_t len)
{
  int i;
  size_t limit;

  i = 0;
  limit = 0;
  if ((*needle == 0 && *haystack == 0) || (*needle == 0 && len == 0))
    return ((char *)haystack);
  while (*haystack && len && limit < len)
  {
    i = 0;
    while (limit + i < len && needle[i] && needle[i] == haystack[i])
      ++i;
    if (needle[i] == 0)
      return ((char *)haystack);
    haystack++;
    limit++;
  }
  return (NULL);
}

ArbResult ping_pong(uint8_t *input, size_t len)
{
  if (ft_strnstr(input, "ping", len))
    return _return_short_string(Success, "pong");
  return _return_short_string(Success, "ping");
}


ArbResult	mi_balance(uint8_t *input, size_t len)
{
	uint8_t value[32];
	msg_sender_padded(buf_out);
	account_balance(buf_out, value);
	return _return_success_bebi32(value);
}

int handler(size_t argc)
{
  // Save the function calldata (selector(bytes4) + fn_args(bytes))
  uint8_t argv[argc];
  read_args(argv); // 4 btes (firma del a funcion)

  // Define the registry array with registered functions
  FunctionRegistry registry[] = {
    // balance()
    // address: 0x82B36e0c4C6E9cafA5CeACf481fa13e6CE2ac385
    // uint256: 100000000000000000000....32bytes
    // string: "242242121"
    // bytes32: 0x82B36ac385
      {to_function_selector("calldata_len()"), calldata_len},
      {to_function_selector("ping_pong(bytes32)"), ping_pong},
	  {to_function_selector("mi_balance()"), mi_balance},
	//  {to_function_selector("accounted_balance()"), accounted_balance},
    //  {to_function_selector("hola_mundo()"), hola_mundo}, // Add more functions as needed here
  };

  uint32_t signature = *((uint32_t *)argv); // Take function selector

  // Call the function based on the signature
  ArbResult res = call_function(registry,
                                sizeof(registry) / sizeof(registry[0]),
                                signature, argv + 4, argc - 4 // Exclude the selector from calldata
  );
  return (write_result(res.output, res.output_len), res.status);
}

ENTRYPOINT(handler)
