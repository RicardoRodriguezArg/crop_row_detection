#!/bin/bash
export ANSIBLE_CONFIG=/etc/ansible/ansible.cfg
echo "Deploy and installing Open Drone Map Docker"
ansible-playbook ../map_compiler/playbooks/website/playbook.yml -K --extra-vars "ansible_become_pass=operator"