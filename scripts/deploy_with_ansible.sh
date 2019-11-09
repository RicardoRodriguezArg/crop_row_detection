#!/bin/bash
echo $USER
export ANSIBLE_CONFIG=/etc/ansible/ansible.cfg
#ansible all -m ping
ansible-playbook ../playbook/playbook.yml -K --extra-vars "ansible_become_pass=operator"