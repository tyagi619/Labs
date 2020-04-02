#! /bin/bash

sed -r 'y/abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789/zyxwvutsrqponmlkjihgfedcbaZYWXVUTSRQPONMLKJIHGFEDCBA9876543210/' < $1 >$2
