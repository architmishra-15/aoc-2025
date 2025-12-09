import java.io.File

class Solution(private val filename: String? = null, private val suppliedLines: List<String>? = null) {
    private var values: List<String>

    init {
        values = when {
            suppliedLines != null -> suppliedLines
            filename != null -> File(filename).readLines()
            else -> emptyList()
        }
    }

    fun Part1(): Int {
        val rows = values.size
        if (rows == 0) return 0
        val cols = values[0].length

        var count = 0

        for (i in 0 until rows) {
            // defensive: ensure all rows have same length
            if (values[i].length != cols) {
                throw IllegalStateException("All rows must have the same length (row $i length ${values[i].length} != $cols)")
            }

            for (j in 0 until cols) {
                if (values[i][j] != '@') continue

                var neighbours = 0
                for (di in -1..1) {
                    for (dj in -1..1) {
                        if (di == 0 && dj == 0) continue
                        val ni = i + di
                        val nj = j + dj
                        if (ni in 0 until rows && nj in 0 until cols && values[ni][nj] == '@') {
                            neighbours++
                        }
                    }
                }

                if (neighbours < 4) count++
            }
        }
        return count
    }

    fun Part2(debug: Boolean = true): Int {
        val rows = values.size
        if (rows == 0) return 0
        val cols = values[0].length

        // Create mutable grid
        val grid = values.map { it.toCharArray() }.toMutableList()

        var totalRemoved = 0
        var iteration = 0

        while (true) {
            iteration++

            // Find all '@' cells with fewer than 4 '@' neighbors
            val toRemove = mutableListOf<Pair<Int, Int>>()

            for (i in 0 until rows) {
                for (j in 0 until cols) {
                    if (grid[i][j] != '@') continue

                    // Count '@' neighbors in all 8 directions
                    var neighbours = 0
                    for (di in -1..1) {
                        for (dj in -1..1) {
                            if (di == 0 && dj == 0) continue
                            val ni = i + di
                            val nj = j + dj
                            if (ni in 0 until rows && nj in 0 until cols && grid[ni][nj] == '@') {
                                neighbours++
                            }
                        }
                    }

                    // If fewer than 4 neighbors, mark for removal
                    if (neighbours < 4) {
                        toRemove.add(i to j)
                    }
                }
            }

            // If nothing to remove, we're done
            if (toRemove.isEmpty()) {
                if (debug) println("No more removals at iteration $iteration. Stopping.")
                break
            }

            // Remove all marked cells
            for ((i, j) in toRemove) {
                grid[i][j] = '.'
            }

            totalRemoved += toRemove.size

            if (debug) {
                println("Iteration $iteration: removed ${toRemove.size} (cumulative removed = $totalRemoved)")
            }
        }

        if (debug) {
            println("Finished. Total removed = $totalRemoved")
        }

        // Update values for potential inspection
        values = grid.map { String(it) }
        return totalRemoved
    }
}

fun main() {
    val filename = "input"
    val s = Solution(filename = filename)
    println("Part 1: ${s.Part1()}")
    println("Part 2: ${s.Part2()}")
}