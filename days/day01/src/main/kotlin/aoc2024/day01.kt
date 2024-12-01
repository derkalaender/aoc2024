package aoc2024

import com.github.ajalt.clikt.core.CliktCommand
import com.github.ajalt.clikt.core.main
import com.github.ajalt.clikt.parameters.arguments.argument
import com.github.ajalt.clikt.parameters.types.file
import kotlin.math.abs

class AOC : CliktCommand() {
    private val input by argument().file(mustExist = true, mustBeReadable = true)

    override fun run() {
        val inputData = readInput()

        echo("Answer 1: ${partOne(inputData)}")
        echo("Answer 2: ${partTwo(inputData)}")
    }

    /**
     * Reads the input file and maps it to the pair of location ID lists.
     *
     * @return the two mismatched location ID lists
     */
    private fun readInput(): Pair<List<Int>, List<Int>> {
        val leftIDs = mutableListOf<Int>()
        val rightIDs = mutableListOf<Int>()

        // read input
        input.bufferedReader().lineSequence().forEach { l ->
            val (left, right) = l.split("   ")
            leftIDs += left.toInt()
            rightIDs += right.toInt()
        }

        return leftIDs to rightIDs
    }

    private fun partOne(input: Pair<List<Int>, List<Int>>): Int {
        // sort both small -> big
        val leftIDs = input.first.sorted()
        val rightIDs = input.second.sorted()

        // pair up again, compute delta and sum
        return (leftIDs zip rightIDs)
            .sumOf { (l, r) -> abs(l - r) }
    }

    private fun partTwo(input: Pair<List<Int>, List<Int>>): Int {
        val (leftIDs, rightIDs) = input

        // for each number of left list, count occurrences in right list
        // then multiply by count
        // finally sum
        val result = leftIDs
            .asSequence()
            .map { l -> l to rightIDs.count { r -> r == l } }
            .map { (id, count) -> id * count }
            .sum()
        return result
    }
}

fun main(args: Array<String>) = AOC().main(args)
