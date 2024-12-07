import { createPublicClient, http, parseAbi } from "viem"
import { arbitrumSepolia } from "viem/chains"
import "dotenv/config"

// ABI del contrato (ajusta según tu contrato y funciones)
const ABI = parseAbi([
  "function is_active() view returns (bool)",
  "function get_question_text(uint8) view returns (string)"
])

// Dirección del contrato desplegado
const CONTRACT_ADDRESS = "0xbe385839383f18825b30c5011179198c0239dedb"

// Crear cliente público para leer estado
const client = createPublicClient({
  chain: arbitrumSepolia,
  transport: http(),
})

async function main() {
  const active = await client.readContract({
    abi: ABI,
    address: CONTRACT_ADDRESS,
    functionName: "is_active"
  })

  if (!active) {
    console.log("El challenge no está activo en este momento.")
	return;
  }

  console.log("El challenge está activo. Estas son las preguntas:")

  for (let i = 0; i < 4; i++) {
    const question = await client.readContract({
      abi: ABI,
      address: CONTRACT_ADDRESS,
      functionName: "get_question_text",
      args: [i]
    })
    console.log(`Pregunta ${i + 1}: ${question}`)
  }
}

main().catch((err) => console.error(err))

//import { createPublicClient, http, parseAbi, stringToHex } from "viem"
//import { arbitrumSepolia } from "viem/chains"
//import "dotenv/config"

//const ABI = parseAbi([
//  "function hola_mundo() view returns (string)",
//  "function calldata_len() view returns (uint256)",
//  "function ping_pong(bytes32) view returns (string)",
//])

//const client = createPublicClient({
//  chain: arbitrumSepolia,
//  transport: http(),
//})

//// https://sepolia.arbiscan.io/address/0x6a5a8573fe27c42ce960dcb7a19cf957f0e8f837
//const CONTRACT_ADDRESS = "0x67aa7e06942a177dad98ac58fa5beba05df2e60a"

//async function main() {
//  const result = await client.readContract({
//    abi: ABI,
//    address: CONTRACT_ADDRESS,
//    functionName: "hola_mundo"
//  })

//  console.debug(`Contract: ${result}`)
//}

//main()
