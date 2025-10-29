# test_runner.ps1 - Automated test runner for assembler normalization tests
# Usage: .\test_runner.ps1

Write-Host "Running assembler normalization tests..." -ForegroundColor Green

# Define test cases with expected .pre content
$tests = @(
    @{
        Name = "test_norm_commas"
        ExpectedLines = @(
            "COPY A, B",
            "LOAD X",
            "A: CONST 1",
            "B: CONST 2",
            "X: SPACE 1"
        )
    },
    @{
        Name = "test_norm_plus"
        ExpectedLines = @(
            "LOAD A + 1",
            "A: SPACE 2"
        )
    },
    @{
        Name = "test_norm_macro_arg_commas"
        ExpectedLines = @(
            "COPY A, B",
            "A: CONST 10",
            "B: CONST 20"
        )
    },
    @{
        Name = "test_norm_macro_substitution"
        ExpectedLines = @(
            "LOAD A + 1",
            "A: CONST 3"
        )
    },
    @{
        Name = "test_norm_trailing_comma"
        ExpectedLines = @(
            "COPY A,  erro sintático",
            "A: CONST 7"
        )
    }
)

$allPassed = $true

foreach ($test in $tests) {
    Write-Host "Testing $($test.Name)..." -ForegroundColor Yellow
    
    # Run assembler
    $null = & .\assembler.exe "$($test.Name).asm"
    
    if (-not (Test-Path "$($test.Name).pre")) {
        Write-Host "  FAIL: No .pre file generated" -ForegroundColor Red
        $allPassed = $false
        continue
    }
    
    # Read actual output
    $actualLines = Get-Content "$($test.Name).pre"
    
    # Compare line by line
    $testPassed = $true
    if ($actualLines.Count -ne $test.ExpectedLines.Count) {
        Write-Host "  FAIL: Line count mismatch. Expected $($test.ExpectedLines.Count), got $($actualLines.Count)" -ForegroundColor Red
        $testPassed = $false
    } else {
        for ($i = 0; $i -lt $actualLines.Count; $i++) {
            if ($actualLines[$i] -ne $test.ExpectedLines[$i]) {
                Write-Host "  FAIL: Line $($i + 1) mismatch" -ForegroundColor Red
                Write-Host "    Expected: '$($test.ExpectedLines[$i])'" -ForegroundColor Red
                Write-Host "    Actual:   '$($actualLines[$i])'" -ForegroundColor Red
                $testPassed = $false
            }
        }
    }
    
    if ($testPassed) {
        Write-Host "  PASS" -ForegroundColor Green
    } else {
        $allPassed = $false
    }
    
    # Clean up generated files
    Remove-Item -Path "$($test.Name).pre" -ErrorAction SilentlyContinue
    Remove-Item -Path "$($test.Name).o1" -ErrorAction SilentlyContinue
    Remove-Item -Path "$($test.Name).o2" -ErrorAction SilentlyContinue
}

Write-Host ""
if ($allPassed) {
    Write-Host "All tests PASSED!" -ForegroundColor Green
    exit 0
} else {
    Write-Host "Some tests FAILED!" -ForegroundColor Red
    exit 1
}