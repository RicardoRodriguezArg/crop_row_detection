pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                echo 'Building..'
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
            }
        }
        stage('Ansible Deploy') {

            //steps {
            //	ansiColor('xterm') {
			//			    ansiblePlaybook(
			//			        playbook: 'playbook/playbook.yml',
			//			        inventory: '/etc/ansible/hosts',
			//			        credentialsId: '/home/ci_operator/.ssh/id_rsa',
			//			        colorized: true)
			//}
              echo 'Executing Deploying Scripts'
              dir('scripts')
              {
              echo 'Applying execution rigths'
              sh 'chmod +x ./deploy_with_ansible.sh'
              echo 'Calling Ansibles scritps'
              sh './deploy_with_ansible.sh'
              }
            
            
        }
        
    }
}
