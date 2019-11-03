#!/bin/bash
echo "operator" | sudo -S ../playbook/ansible-playbook -i /etc/ansible/hosts playbook.yml -K