import { createPublicClient, http, parseAbi, stringToHex } from "viem"
import { arbitrumSepolia } from "viem/chains"
import "dotenv/config"

const ABI = parseAbi([
  "function hola_mundo() view returns (string)",
  "function calldata_len() view returns (uint256)",
  "function ping_pong(bytes32) view returns (string)",
  "function mi_balance() view returns (address)",
  "function accounted_balance(address) view returns (uint256)",
])

const client = createPublicClient({
  chain: arbitrumSepolia,
  transport: http(),
})

// https://sepolia.arbiscan.io/address/0x6a5a8573fe27c42ce960dcb7a19cf957f0e8f837
const CONTRACT_ADDRESS = "0x73009c93c4e7bd889f096c409881bbbe64fd6d12"

async function main() {
  const result = await client.readContract({
    abi: ABI,
    address: CONTRACT_ADDRESS,
	account: "0x871E2bEcae8DA95082Aa36492a2FB2c13f1bCD0F",
    functionName: "mi_balance",
  })
  console.debug(`Contract: ${result}`)
}

main()
