plugins {
    kotlin("jvm") version "2.1.0"
}

group = "aoc2024"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {
    implementation("com.github.ajalt.clikt:clikt:5.0.1")
}

kotlin {
    jvmToolchain(23)
}
