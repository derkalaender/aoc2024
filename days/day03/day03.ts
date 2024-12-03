import {parseArgs} from "@std/cli/parse-args";

async function readInput(path: string): Promise<string> {
  return await Deno.readTextFile(path);
}

function partOne(input: string): number {
  // regex to match mul(num1,num2) anywhere in the string
  const r = /mul\((\d{1,3}),(\d{1,3})\)/g;
  const matches = input.matchAll(r);

  let sum = 0;
  for (const match of matches) {
    // match is an array containing: the whole mul instruction, the first number, the second number
    // convert to number with unary plus
    sum += +match[1] * +match[2];
  }
  return sum;
}

function partTwo(input: string): number {
  // regex to match mul(num1,num2) anywhere in the string
  // but also match do() and don't() so we can enable or disable adding to the running sum
  const r = /do\(\)|don't\(\)|mul\((\d{1,3}),(\d{1,3})\)/g;
  const matches = input.matchAll(r);

  let sum = 0;
  let enabled = true;
  for (const match of matches) {
    // match is an array containing either
    // - do()
    // - don't()
    // - the whole mul instruction, the first number, the second number

    switch (match[0]) {
      case "do()":
        enabled = true;
        break;
      case "don't()":
        enabled = false;
        break;
      default:
        if (enabled) {
          // convert to number with unary plus
          sum += +match[1] * +match[2];
        }
    }
  }
  return sum;
}

if (import.meta.main) {
  const args = parseArgs(Deno.args);
  if (args._.length < 1) {
    console.error("Missing input path");
    Deno.exit(1);
  }
  const inputPath = args._[0] as string;

  try {
    const input = await readInput(inputPath);

    console.log(`Answer 1: ${partOne(input)}`);
    console.log(`Answer 2: ${partTwo(input)}`);
  } catch (e) {
    console.error(e);
    Deno.exit(1);
  }
}
