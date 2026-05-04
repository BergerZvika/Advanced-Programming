#!/usr/bin/env bash
for bin in $(ls build/0* 2>/dev/null | sort); do
    echo ""
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    "$bin"
    echo ""
    read -p "  Press Enter for next demo..." || true
done
echo "All demos complete."
