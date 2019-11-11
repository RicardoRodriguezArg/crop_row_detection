#!/bin/bash
export ANSIBLE_CONFIG=/etc/ansible/ansible.cfg
ansible-playbook ../playbook/playbook.yml -K --extra-vars "ansible_become_pass=operator"
pwd
echo "deploying web site on target machine"
ansible-playbook ../map_compiler/playbooks/odm/odm.yml -K --extra-vars "ansible_become_pass=operator"