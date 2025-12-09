package main

import (
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

type Range struct {
	Start int
	End   int
}


func part1(scan []byte) {
	// Find the blank line separator
	pos := 0
	for idx := range scan {
		if idx < len(scan)-1 && scan[idx] == '\n' && scan[idx+1] == '\n' {
			break
		}
		pos = idx + 1
	}

	var ranges []Range

	rangeSection := string(scan[:pos])
	lines := strings.Split(strings.TrimSpace(rangeSection), "\n")
	
	for _, line := range lines {
		if line == "" {
			continue
		}
		parts := strings.Split(line, "-")
		if len(parts) == 2 {
			val1, err1 := strconv.Atoi(parts[0])
			val2, err2 := strconv.Atoi(parts[1])
			if err1 == nil && err2 == nil {
				ranges = append(ranges, Range{Start: val1, End: val2})
			}
		}
	}

	var values []int
	if pos+2 < len(scan) {
		valueSection := string(scan[pos+2:])
		valueLines := strings.Split(strings.TrimSpace(valueSection), "\n")
		
		for _, line := range valueLines {
			if line == "" {
				continue
			}
			val, err := strconv.Atoi(strings.TrimSpace(line))
			if err != nil {
				fmt.Printf("Could not convert %s to int: %s\n", line, err)
				continue
			}
			values = append(values, val)
		}
	}

	fmt.Println("Fresh ID Ranges:")
	for _, r := range ranges {
		fmt.Printf("%d-%d\n", r.Start, r.End)
	}
	fmt.Printf("Total ranges: %d\n\n", len(ranges))
	
	fmt.Println("Available Ingredient IDs (first 10):")
	for i := 0; i < len(values) && i < 10; i++ {
		fmt.Printf("%d: %d\n", i, values[i])
	}
	fmt.Printf("Total ingredients: %d\n\n", len(values))

	freshCount := 0
	
	for _, ingredientID := range values {
		isFresh := false
		for _, r := range ranges {
			if ingredientID >= r.Start && ingredientID <= r.End {
				isFresh = true
				break
			}
		}
		if isFresh {
			freshCount++
		}
	}

	fmt.Printf("\nNumber of fresh ingredient IDs: %d\n", freshCount)
}

func part2(scan []byte) {

	pos := 0
	for idx := range scan {
		if idx < len(scan)-1 && scan[idx] == '\n' && scan[idx+1] == '\n' {
			break
		}
		pos = idx + 1
	}

	var ranges []Range

	rangeSection := string(scan[:pos])
	lines := strings.Split(strings.TrimSpace(rangeSection), "\n")
	
	for _, line := range lines {
		if line == "" {
			continue
		}
		parts := strings.Split(line, "-")
		if len(parts) == 2 {
			val1, err1 := strconv.Atoi(parts[0])
			val2, err2 := strconv.Atoi(parts[1])
			if err1 == nil && err2 == nil {
				ranges = append(ranges, Range{Start: val1, End: val2})
			}
		}
	}

	sortedRanges := make([]Range, len(ranges))
	copy(sortedRanges, ranges)
	
	// Simple bubble sort (or use sort.Slice)
	for i := 0; i < len(sortedRanges); i++ {
		for j := i + 1; j < len(sortedRanges); j++ {
			if sortedRanges[j].Start < sortedRanges[i].Start {
				sortedRanges[i], sortedRanges[j] = sortedRanges[j], sortedRanges[i]
			}
		}
	}
	

	var merged []Range
	if len(sortedRanges) > 0 {
		current := sortedRanges[0]
		
		for i := 1; i < len(sortedRanges); i++ {
			next := sortedRanges[i]
			// Check if ranges overlap or are adjacent
			if next.Start <= current.End + 1 {
				// Merge: extend current range if needed
				if next.End > current.End {
					current.End = next.End
				}
			} else {
				// No overlap, save current and start new range
				merged = append(merged, current)
				current = next
			}
		}
		merged = append(merged, current)
	}

	// Count total IDs in merged ranges
	totalFreshIDs := 0
	fmt.Println("Merged ranges:")
	for _, r := range merged {
		count := r.End - r.Start + 1
		totalFreshIDs += count
		fmt.Printf("  %d-%d (%d IDs)\n", r.Start, r.End, count)
	}
	
	fmt.Printf("\nPart 2 - Total unique fresh ingredient IDs: %d\n", totalFreshIDs)
}

func main() {
	filename := "input.txt"
	f, err := os.Open(filename)
	if err != nil {
		fmt.Println("Could not open file")
		return
	}
	fmt.Println("File Read")
	defer f.Close()

	scan, err := io.ReadAll(f)
	if err != nil {
		fmt.Println("Error in reading file: ", err)
		return
	}

	// part1(scan)
	part2(scan)
}
