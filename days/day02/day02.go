package main

import (
	"bufio"
	"log"
	"os"
	"strconv"
	"strings"
)

type Level int
type Report []Level
type Data []Report

func readInput(path string) (Data, error) {
	file, err := os.Open(path)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	data := Data{}

	scanner := bufio.NewScanner(file)
	// go through line by line
	for scanner.Scan() {
		line := scanner.Text()
		split := strings.Split(line, " ")

		// parse line as report (ints seperated by a single space)
		report := make(Report, len(split))
		for i, s := range split {
			level, err := strconv.Atoi(s)
			if err != nil {
				return nil, err
			}
			report[i] = Level(level)
		}

		// append report
		data = append(data, report)
	}

	return data, nil
}

func partOne(data Data) int {
	isSafe := func(r Report) bool {
		if len(r) < 2 {
			return true
		}

		// find out if increasing
		// but if the first two are the same, that is considered unsafe
		if r[0] == r[1] {
			return false
		}
		increasing := r[0] < r[1]

		prev := r[0]
		for i, curr := range r {
			if i == 0 {
				continue
			}
			// we cannot switch between increasing & decreasing, nor can they be the same or too far apart
			if (increasing && curr < prev) || (!increasing && prev < curr) || prev == curr || prev-curr > 3 || prev-curr < -3 {
				return false
			}
			prev = curr
		}
		return true
	}

	safeCount := 0
	for _, r := range data {
		if isSafe(r) {
			safeCount++
		}
	}
	return safeCount
}

func main() {
	args := os.Args
	// get path argument
	if len(args) < 2 {
		log.Fatal("No input path provided")
	}
	path := args[1]

	// read & parse input
	data, err := readInput(path)
	if err != nil {
		log.Fatal(err)
	}

	log.Printf("Answer 1: %d", partOne(data))
}