#!/bin/bash
echo "operator" | sudo -S -u ci_operator ansible-playbook -i /etc/ansible/hosts ../playbook/playbook.yml -K