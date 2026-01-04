#!/bin/bash

# Zkompilujeme program
make clean > /dev/null 2>&1
make > /dev/null 2>&1

if [ ! -f "./main" ]; then
    echo "Chyba: Program se nepodarilo zkompilovat"
    exit 1
fi

echo "Testování programu..."
echo "===================="

success_count=0
fail_count=0

# Projdeme všechny .in soubory
for input_file in pub*.in; do
    # Získáme basename (např. pub00)
    base="${input_file%.in}"
    
    # Projdeme všechny varianty (_a, _b, _c, ...)
    for out_file in ${base}_*.out; do
        if [ -f "$out_file" ]; then
            # Získáme variantu (např. pub00_a)
            variant="${out_file%.out}"
            err_file="${variant}.err"
            
            # Zjistíme parametry z názvu souboru
            suffix="${variant##*_}"
            
            # Nastavíme parametry podle suffixu
            case $suffix in
                a) params="" ;;
                b) params="-s 1" ;;
                c) params="-s 2" ;;
                d) params="-l 0" ;;
                e) params="-l 5" ;;
                f) params="-c" ;;
                *) params="" ;;
            esac
            
            # Spustíme program
            ./main $params < "$input_file" > /tmp/test_output.txt 2> /tmp/test_error.txt
            
            # Porovnáme výstup
            if diff -q "$out_file" /tmp/test_output.txt > /dev/null 2>&1; then
                out_status="✓"
                ((success_count++))
            else
                out_status="✗"
                ((fail_count++))
            fi
            
            # Porovnáme chybový výstup (pokud existuje)
            if [ -f "$err_file" ]; then
                if diff -q "$err_file" /tmp/test_error.txt > /dev/null 2>&1; then
                    err_status="✓"
                else
                    err_status="✗"
                    if [ "$out_status" = "✓" ]; then
                        ((success_count--))
                        ((fail_count++))
                        out_status="✗"
                    fi
                fi
                echo "[$out_status] $variant (params: $params) - stdout: $out_status, stderr: $err_status"
            else
                echo "[$out_status] $variant (params: $params)"
            fi
            
            # Pokud test selhal, ukážeme rozdíly
            if [ "$out_status" = "✗" ]; then
                echo "    Rozdíly v stdout:"
                diff "$out_file" /tmp/test_output.txt | head -5 | sed 's/^/    /'
            fi
        fi
    done
done

echo "===================="
echo "Úspěšné: $success_count"
echo "Neúspěšné: $fail_count"

# Uklidíme
rm -f /tmp/test_output.txt /tmp/test_error.txt

if [ $fail_count -eq 0 ]; then
    echo "Všechny testy prošly! ✓"
    exit 0
else
    echo "Některé testy selhaly."
    exit 1
fi
